#include<iostream>
#include<string>
#include <functional>
#include "Graph.h"

using namespace std;

void safe_call(std::function <void()> func) {
	try {
		func();
	}
	catch (const char* exception) {
		std::cout << "Exception caught: " << exception << std::endl;
	}
}

int main() {
	setlocale(LC_ALL, "");
	Graph graph;
	cout << "Добавление вершин:" << endl;
	safe_call([&]() {graph.addVertex("Natalya"); }); //0
	safe_call([&]() {graph.addVertex("Sergey"); }); //1
	safe_call([&]() {graph.addVertex("Anna"); }); //2
	safe_call([&]() {graph.addVertex("Tanya"); }); //3
	safe_call([&]() {graph.addVertex("Maria"); }); //4
	safe_call([&]() {graph.addVertex("Larisa"); }); //5
	safe_call([&]() {graph.addVertex("Alex"); }); //6
	safe_call([&]() {graph.addVertex("Dennis"); }); //7
	safe_call([&]() {graph.addVertex("Misha"); }); //8
	safe_call([&]() {graph.addVertex("Oleg"); }); //9
	cout << "/////////////////////////////////////////////" << endl;

	cout << "Добавление ребер:" << endl;
	safe_call([&]() {graph.addEdge("Natalya", "Sergey"); });
	safe_call([&]() {graph.addEdge("Sergey", "Anna"); });
	safe_call([&]() {graph.addEdge("Tanya", "Sergey"); });
	safe_call([&]() {graph.addEdge("Maria", "Anna"); });
	safe_call([&]() {graph.addEdge("Larisa", "Sergey"); });
	safe_call([&]() {graph.addEdge("Larisa", "Dennis"); });
	safe_call([&]() {graph.addEdge("Dennis", "Misha"); });
	safe_call([&]() {graph.addEdge("Oleg", "Maria"); });
	safe_call([&]() {graph.addEdge("Alex", "Natalya"); });
	cout << "/////////////////////////////////////////////" << endl;

	//safe_call([&]() {graph.printVertex("Natalya"); });
	//safe_call([&]() {graph.printVertex("Sergey"); });
	//safe_call([&]() {graph.printVertex("Anna"); });
	cout << "Вывод всех вершин и смежных им вершин:" << endl;
	safe_call([&]() {graph.printAllVertexAll(); });
	cout << "/////////////////////////////////////////////" << endl;

	//cout << "Проверка смежности пар вершин:" << endl;
	//safe_call([&]() {cout << graph.connectVertex("Natalya", "Sergey") << endl; });
	//safe_call([&]() {cout << graph.connectVertex("Tanya", "Sergey") << endl; });
	//safe_call([&]() {cout << graph.connectVertex("Anna", "Sergey") << endl; });

	cout << "Проверка смежности пар вершин через 3 рукопожатия:" << endl;
	safe_call([&]() {graph.connectVertexFor3("Natalya"); });
}