import os
import json
import requests
from py2neo import Graph
from py2neo import Path, authenticate
# set up authentication parameters
authenticate("localhost:7474", "neo4j", "password")

# connect to authenticated graph database
#graph = Graph("http://localhost:7474/db/data/")

# Connect to graph and add constraints.
neo4jUrl = os.environ.get('NEO4J_URL',"http://localhost:7474/db/data/")
graph = Graph(neo4jUrl,secure=False)

files=os.listdir("./workshop_dataset1")
data = {}
files_done = 0
for file in files:
    with open("./workshop_dataset1/" + file, 'rb') as f:
        files_done = files_done + 1
	print str(files_done) + " fetching " + file + " done"
        data = json.load(f)

# Build query.
	query = """
	WITH {data} as data
	UNWIND extract (key in keys(data) | data[key]) as tdata
	MERGE (tweet:Tweet {tid:tdata.tid}) 
		ON CREATE SET tweet.tid = tdata.tid, tweet.text = tdata.tweet_text, tweet.type = tdata.type, tweet.location = tdata.location
	MERGE (user:User {author:tdata.author})
		ON CREATE SET user.author = tdata.author
	MERGE (user)-[:POST]->(tweet)

	FOREACH (tag IN tdata.hashtags | MERGE (hashtag:Hashtag {name:tag}) MERGE (tweet)-[:TAGS]->(hashtag))
	FOREACH (key IN tdata.keywords_processed_list | MERGE (keyword:Keyword {name:key}) MERGE (tweet)-[:CONTAINS_KEY]->(keyword))
	FOREACH (mention IN tdata.mentions | MERGE (men:Mention {name:mention}) MERGE (tweet)-[:MENTIONS]->(men))
	FOREACH (list IN tdata.url_list | MERGE (url:Link {name:list}) MERGE (tweet)-[:CONTAINS_URL]->(url))
	WITH user,tweet,tdata
	MATCH (user)-[:POST]->(tweet) where tweet.type="retweet"
		MERGE (tweet2:Tweet {tid:tdata.retweet_source_id})
			CREATE (tweet)-[:RETWEET]->(tweet2)
	WITH user,tweet,tdata
	MATCH (user)-[:POST]->(tweet) where tweet.type="Reply"
		MERGE (tweet3:Tweet {tid:tdata.replyto_source_id})
			CREATE (tweet)-[:REPLYTO]->(tweet3)
	"""
	# statement = "MERGE (n:Person {name:{N}}) RETURN n"
	results = graph.run(query, data = data)
	tx = graph.begin()

# def add_names(*names):
#     for name in names:
#         tx.append(statement, {"N": name})
#     tx.process()
	tx.commit()
	print str(files_done) + " graphing " + file + " done"