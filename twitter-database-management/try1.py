import os
# import requests
from py2neo import authenticate, Graph, Path, Node, Relationship
# from py2neo import neo4j
authenticate("localhost:7474", "neo4j", "password")
graph = Graph("http://localhost:7474/db/data/")

# neo4jUrl = os.environ.get('NEO4J_URL',"http://localhost:7474/db/data/")
# graph = neo4j.GraphDatabaseService(neo4jUrl)

# neo4j.CypherQuery(graph, "CREATE CONSTRAINT ON (q:Question) ASSERT q.id IS UNIQUE;").run()
# neo4j.CypherQuery(graph, "CREATE as:User {author:'nitesh', author_profile_image: 'https://pbs.twimg.com/profile_images/691509520951066624/ujzi7oLA_normal.jpg', author_screen_name: 'zlando', author_id: '37919483'}").run()

files=os.listdir("./workshop_dataset1")
files_done = 0
for file in files:
	with open("./workshop_dataset1/" + file, 'rb') as f:
		files_done = files_done + 1
		print  file + " done"
		file_data = json.load(f)
        for k in file_data.keys():
			tweet_data = file_data[k]
			alice = Node("user", name="Alice")
			bob = Node("Person", name="Bob")
			alice_knows_bob = Relationship(alice, "KNOWS", bob)


# graph.create(alice)
# graph.create(bob)
graph.create(alice_knows_bob)