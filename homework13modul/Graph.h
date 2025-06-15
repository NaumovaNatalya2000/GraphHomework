#pragma once
#include<iostream>
#include<string>
#define MAX_VERTICES 10
#define MAX_EDGES 10

//будет использоваться Список смежных вершин

class Graph
{
	//структура ребра
	struct Edge {
		//в какую вершину ведет
		std::string vertexWhere;
		//конструктор
		Edge(){};
	};
	//структура вершины
	struct Vertex {
		//имя вершины
		std::string vName;
		//ребра, ведущие из вершины
		Edge adj_vertexes[MAX_EDGES];
		int edgeCount = 0;
	};

public:
	//конструктор
	Graph();
	//добавление вершины
	void addVertex(const std::string& name);
	//поиск индекса нужной вершины по имени - выводит -1 если вершина не найдена
	int searchIndex(const std::string& name);
	//добавление ребра
	void addEdge(const std::string& name1, const std::string& name2);
	//вывод всех смежных вершин вершины по имени
	void printVertex(const std::string& name);
	//вывод всех вершин
	void printAllVertex();
	//вывод всех вершин и смежных им вершин
	void printAllVertexAll();
	//является ли вершина смежной
	bool connectVertex(const std::string& v1, const std::string& v2);
	//поиск смежных вершин по 3 рукопожатиям - алгоритм обхода в ширину
	bool connectVertexFor3(const std::string& v1, const std::string& v2);
private:
	//массив вершин
	Vertex vertexes[MAX_VERTICES];
	//количество вершин
	int vertexCount;

};

