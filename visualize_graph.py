import json
import networkx as nx
import matplotlib.pyplot as plt
import numpy as np

def main():
	# Load the graph data from JSON
	with open('graph.json', 'r') as f:
		data = json.load(f)
	
	G = nx.Graph()
	
	# Add vertices using the vertex id as the node and storing the name as an attribute
	for vertex in data.get("vertices", []):
		node_id = vertex["id"]
		G.add_node(node_id, name=vertex["name"])
	
	# Add edges using the id from the "from" and "to" vertices
	for edge in data.get("edges", []):
		from_id = edge["from"]["id"] # Using name instead of id
		to_id = edge["to"]["id"]
		# Assuming "weight" contains a dictionary with a "name" key for the label
		label = edge["weight"]["name"]
		G.add_edge(from_id, to_id, label=label)

	# Make the figure bigger
	plt.figure(figsize=(12, 8))
	
	# How the positions are calculated
	pos = nx.spring_layout(G, scale=20, k=3/np.sqrt(G.order()),
				iterations=300)

	# Create a dictionary for node degrees to dynamically size them based off their degree
	degrees = dict(G.degree)

	# Create a dictionary mapping node ID to vertex name
	labels = nx.get_node_attributes(G, 'name');

	# Draw the graph using vertex names and labels
	nx.draw(
		G, 
		pos, 
		labels=labels,
		with_labels=True, 
		node_color='lightblue', 
		font_size=6,
		nodelist=degrees,
		node_size=[degrees[k]*100 for k in degrees])
	
	# Draw edge labels
	edge_labels = nx.get_edge_attributes(G, 'label')
	nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_size= 6)
	
	plt.show()

if __name__ == "__main__":
	main()