/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main()
{
	int w, h, mazeNumber=1;
	char c;
	vector<vector<char> > maze;

	cin >> w >> h;
	while(w != 0 || h != 0) {
		maze.clear();

		for(int i=0; i<h; ++i) {
			maze.push_back(vector<char>());
			for(int j=0; j<w; ++j) {
				cin >> c;
				maze[maze.size()-1].push_back(c);
			}
			cin.ignore();	//ignorar salto de línea
		}

		//construir grafo
		vector<vector<int> > graph;

		for(int i=0; i<h*2 + 1; ++i) {
			for(int j=0; j<w+(i % 2); ++j) {		//dependiendo de la fila es la cantidad de celdas que hay en el maze
				graph.push_back(vector<int>());
			}
		}

		for(int i=0; i<maze.size(); ++i) {
			for(int j=0; j<maze[i].size(); ++j) {
				if(maze[i][j] == '/') 
				{
					//indice primer vértice afectado
					int firstVertex = i * 2 * w + i + j;

					//primer arista
					graph[ firstVertex ].push_back( firstVertex + w);
					graph[ firstVertex + w].push_back( firstVertex );

					int secondVertex = firstVertex + w + 1;

					//segunda arista
					graph[ secondVertex ].push_back( secondVertex + w );
					graph[ secondVertex + w ].push_back( secondVertex );
				}
				else
				{
					int firstVertex = i * 2 * w + i + j;
					int secondVertex = firstVertex + w + 1;

					//primer arista
					graph[ firstVertex ].push_back( secondVertex );
					graph[ secondVertex ].push_back( firstVertex );

					//segunda arista
					graph[ firstVertex + w ].push_back( secondVertex + w );
					graph[ secondVertex + w ].push_back( firstVertex + w );
				}
			}
		}

		//ya tengo el grafo. Busquemos vértices valencia uno y los marquemos así como todos los vértices en el camino que definen
		set<int> visited;
		for(int i=0; i<graph.size(); ++i) {
			if(visited.find(i) == visited.end()) {
				if(graph[i].size() == 1) {
					visited.insert(i);
					int nextVertex = graph[i][0];
					int previousVertex = i;
					while(graph[nextVertex].size() > 1) {
						visited.insert(nextVertex);
						int tmp = nextVertex;
						nextVertex = graph[nextVertex][0] == previousVertex ? graph[nextVertex][1] : graph[nextVertex][0];
						previousVertex = tmp;
					}
					visited.insert(nextVertex);
				}
			}		
		}

		//ahora en visited están todos los vértices que no forman parte de ciclos. Busquemos ahora los que sí forman parte de ciclos (los que no están en visited), cuando encontremos uno
		//aumentamos contador de ciclos encontrados y recorremos el ciclo contando su longitud y marcando los vértices.
		int ccs = 0;
		int longestCycle = -1;
		for(int i=0; i<graph.size(); ++i) {
			if(visited.find(i) == visited.end()) {	//todos estos vértices encontrados tienen valencia dos
				ccs++;

				visited.insert(i);
				int nextVertex = graph[i][0];
				int previousVertex = i;
				int cycleLength = 1;
				while(nextVertex != i) {
					cycleLength++;
					visited.insert(nextVertex);
					int tmp = nextVertex;
					nextVertex = graph[nextVertex][0] == previousVertex ? graph[nextVertex][1] : graph[nextVertex][0];
					previousVertex = tmp;
				}
				longestCycle = max(cycleLength, longestCycle);
			}
		}

		cout << "Maze #" << mazeNumber << ":" << endl;
		if(ccs > 0) {
			cout << ccs << " Cycles; the longest has length " << longestCycle << "." << endl;
		} else {
			cout << "There are no cycles." << endl;
		}
		cout << endl;

		mazeNumber++;
		cin >> w >> h;
	}


	return 0;
}