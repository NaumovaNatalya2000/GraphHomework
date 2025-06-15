#include "Graph.h"

//конструктор
Graph::Graph()
{
	vertexCount = 0;
}

//добавление вершины - присваиваем имя вершины, количество ребер проставляем 0 и увеличиваем счетчик вершин
void Graph::addVertex(const std::string& name)
{
	//проверка переполненности количества вершин
	if (vertexCount >= MAX_VERTICES) {
		throw "Too many vertex!";
	}
	//проверка: если такая вершина уже существует - выход
	if (searchIndex(name)!=-1) {
		throw "Such an vertex already exists!";
	}
	vertexes[vertexCount].vName = name;
	vertexes[vertexCount].edgeCount = 0;
	vertexCount++;
}

//поиск индекса нужной вершины по имени - выводит -1 если вершина не найдена
int Graph::searchIndex(const std::string& name)
{
	for (int i{}; i < vertexCount; i++) {
		if (vertexes[i].vName == name) {
			return i;
		}
	}
	return -1;
}

//добавление ребра
void Graph::addEdge(const std::string& name1, const std::string& name2)
{
	//если имена совпадают
	if (name1 == name2) {
		throw "The names are the same!";
	}

	//находим индексы вершин по именам
	int indexName1 = searchIndex(name1);
	int indexName2 = searchIndex(name2);
	//проверка: есть ли такие вершины
	if (indexName1 == -1 || indexName2 == -1) {
		throw "Vertex is not found!";
	}
	//проверка: если такое ребро уже существует то выход
	for (int i{}; i < vertexes[indexName1].edgeCount; i++) {
		if (vertexes[indexName1].adj_vertexes[i].vertexWhere == name2) {
			throw "Such an edge already exists!";
		}
	}

	//проверка переполненности ребер вершин
	if (vertexes[indexName1].edgeCount >= MAX_EDGES || vertexes[indexName2].edgeCount >= MAX_EDGES) {
		throw "Too many edges for one of the vertices!";
	}
	vertexes[indexName1].adj_vertexes[vertexes[indexName1].edgeCount].vertexWhere = name2;
	vertexes[indexName1].edgeCount++;

	vertexes[indexName2].adj_vertexes[vertexes[indexName2].edgeCount].vertexWhere = name1;
	vertexes[indexName2].edgeCount++;
}

//вывод всех смежных вершин вершины по имени
void Graph::printVertex(const std::string& name)
{
	int indexVertex = searchIndex(name);
	if (indexVertex == -1) {
		throw "Vertex is not found";
	}
	std::cout << "Vertex name: " << name << std::endl;
	for (int i{}; i < vertexes[indexVertex].edgeCount; i++) {
		std::cout<< vertexes[indexVertex].adj_vertexes[i].vertexWhere << std::endl;
	}
}

//вывод всех вершин
void Graph::printAllVertex()
{
	for (int i{}; i < vertexCount; i++) {
		std::cout << vertexes[i].vName << std::endl;
	}
}

//вывод всех вершин и смежных им вершин
void Graph::printAllVertexAll()
{
	for (int i{}; i < vertexCount; i++) {
		std::cout << "Adjacent vertices for " << vertexes[i].vName << ":" << std::endl;
		for (int j{}; j < vertexes[i].edgeCount; j++) {
			std::cout << vertexes[i].adj_vertexes[j].vertexWhere << std::endl;
		}
	}
}

//является ли одна вершина смежной другой
bool Graph::connectVertex(const std::string& v1, const std::string& v2)
{
	//находим индекс первой вершины
	int indexV1 = searchIndex(v1);
	int indexV2 = searchIndex(v2);
	//если индексы не найдены
	if (indexV1 == -1 || indexV2 == -1) {
		throw "Vertex is not found";
	}
	//если индекс найден
	for (int i{}; i < vertexes[indexV1].edgeCount; i++) {
		if (vertexes[indexV1].adj_vertexes[i].vertexWhere == v2) {
			return true;
		}
	}
	return false;
}

bool Graph::connectVertexFor3(const std::string& v1, const std::string& v2)
{
	//находим индекс первой вершины
	int indexV1 = searchIndex(v1);
	int indexV2 = searchIndex(v2);
	//если индексы не найдены
	if (indexV1 == -1 || indexV2 == -1) {
		throw "Vertex is not found";
	}
	//очередь вершин для обхода - в 0 - индекс вершины, в 1 - глубина
	int queue_to_visit[MAX_VERTICES*4][2];
	int queueCount = 0;
	int head = 0;
	//список посещенных вершин
	bool visited[MAX_VERTICES];
	for (int i{}; i < MAX_VERTICES; i++) {
		visited[i] = false;
	}
	//кладем в очередь начальную вершину
	queue_to_visit[queueCount][0] = indexV1;
	queue_to_visit[queueCount][1] = 0;
	queueCount++;

	//цикл обхода
	while (head < queueCount) {
		int current = queue_to_visit[head][0];
		int depth = queue_to_visit[head][1];
		head++;

		if (current == indexV2 && depth > 0 && depth <= 3) return true;
		if (depth == 3) continue; // не идём глубже

		// Добавляем всех соседей
		for (int i = 0; i < vertexes[current].edgeCount; ++i) {
			int neighbor = searchIndex(vertexes[current].adj_vertexes[i].vertexWhere);
			if (!visited[neighbor]) {
				visited[neighbor] = true;
				queue_to_visit[queueCount][0] = neighbor;
				queue_to_visit[queueCount][1] = depth + 1;
				queueCount++;
			}
		}
	}
	return false;
}
