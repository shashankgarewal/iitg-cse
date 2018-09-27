import json
from py2neo import authenticate, Graph, Path, Node, Relationship
# from py2neo import neo4j
authenticate("localhost:7474", "neo4j", "password")
graph = Graph("http://localhost:7474/db/data/")

with open('workshop_dataset1/2017-11-26.json') as json_data:
    data = json.load(json_data)
    #print data['934934507945312256']
    for r in data:
        # print data
		tweet_data = data[r]
		alice = Node("user", author_id = tweet_data['author_id'])
		bob = Node("tweet", tweet_id = tweet_data['tid'])
		alice_knows_bob = Relationship(alice, tweet_data['type'], bob)
		graph.create(alice_knows_bob)