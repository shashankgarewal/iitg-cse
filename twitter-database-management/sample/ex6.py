import os
import json
import requests
#from py2neo import neo4j
from py2neo import Graph
from py2neo import Path, authenticate
# set up authentication parameters
authenticate("localhost:7474", "neo4j", "password")

# connect to authenticated graph database
#graph = Graph("http://localhost:7474/db/data/")

# Connect to graph and add constraints.
neo4jUrl = os.environ.get('NEO4J_URL',"http://localhost:7474/db/data/")
graph = Graph(neo4jUrl,secure=False)

# Connect to graph and add constraints.
#neo4jUrl = os.environ.get('NEO4J_URL',"http://localhost:7474/db/data/")
#graph = neo4j.GraphDatabaseService(neo4jUrl)

# Add uniqueness constraints.
graph.run("CREATE CONSTRAINT ON (q:Question) ASSERT q.id IS UNIQUE;")
# Build URL.
with open("data.json", 'rb') as f:
	json = json.load(f)
	
	# print(file_data);

	# Build query.
	query = """
	WITH {json} as data
	UNWIND data.items as q
	MERGE (question:Question {id:q.question_id}) ON CREATE
	  SET question.title = q.title, question.share_link = q.share_link, question.favorite_count = q.favorite_count

	MERGE (owner:User {id:q.owner.user_id}) ON CREATE SET owner.display_name = q.owner.display_name
	MERGE (owner)-[:ASKED]->(question)

	FOREACH (tagName IN q.tags | MERGE (tag:Tag {name:tagName}) MERGE (question)-[:TAGGED]->(tag))
	FOREACH (a IN q.answers |
	   MERGE (question)<-[:ANSWERS]-(answer:Answer {id:a.answer_id})
	   MERGE (answerer:User {id:a.owner.user_id}) ON CREATE SET answerer.display_name = a.owner.display_name
	   MERGE (answer)<-[:PROVIDED]-(answerer)
	)

	"""
	statement = "MERGE (n:Person {name:{N}}) RETURN n"
	results = graph.run(query,json=json)

	tx = graph.begin()

	def add_names(*names):
	    for name in names:
	        tx.append(statement, {"N": name})
	    tx.process()

	add_names("Homer", "Marge", "Bart", "Lisa", "Maggie")
	add_names("Peter", "Lois", "Chris", "Meg", "Stewie")
	#tx.append(query,)
	tx.commit()