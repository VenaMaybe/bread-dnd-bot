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
		color = vertex.get("color", "lightblue") # Default is lightblue
		G.add_node(node_id, name=vertex["name"], color=color)
	
	# Add edges using the id from the "from" and "to" vertices
	for edge in data.get("edges", []):
		from_id = edge["from"]["id"] # Using name instead of id
		to_id = edge["to"]["id"]
		# Assuming "weight" contains a dictionary with a "name" key for the label
		label = edge["weight"]["name"]
		edge_id = edge["weight"]["id"]
		G.add_edge(from_id, to_id, label=label, edge_id=edge_id)

	# Make the figure bigger
	plt.figure(figsize=(12, 8))
	
	# How the positions are calculated
	pos = nx.spring_layout(G, scale=20, k=3/np.sqrt(G.order()),
				iterations=300)

	# Create a dictionary for node degrees to dynamically size them based off their degree
	degrees = dict(G.degree)

	# Create a list of colors for the nodes based on the "color" attribute
	node_colors = [G.nodes[node]["color"] for node in G.nodes]

	# Create a dictionary mapping node ID to vertex label that includes the index
	labels = {node: f"{G.nodes[node]['name']}\n{node}" for node in G.nodes()}

	# Draw the graph using vertex names and labels
	nx.draw(
		G, 
		pos, 
		labels=labels,
		with_labels=True, 
		node_color=node_colors, 
		font_size=6,
		nodelist=list(degrees),
		node_size=[degrees[k]*100 for k in degrees])
	
	# Original edge labels from the graph attribute "label"
	edge_labels = {
		(startNode, endNode): f"{d['label']}\nID: {d['edge_id']}" for startNode, endNode, d in G.edges(data=True)
	}

	# Draw the labels for the edges
	nx.draw_networkx_edge_labels(
		G, 
		pos, 
		edge_labels=edge_labels, 
		font_size= 6)
	
	plt.show()

if __name__ == "__main__":
	main()