#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <unordered_map>
#include <utility>
#include <unordered_set>
#include <cassert>
#include <queue>
using namespace std;

vector<string> get_lines(string file_name)
{
    ifstream ifile(file_name);
    if (!ifile.is_open())
    {
        cout << file_name + " not found. " << endl;
        exit(-1);
    }
    vector<string> lines;
    while(!ifile.eof())
    {
        string line;
        getline(ifile, line);
        if (line != "")
        {
            lines.push_back(line);
        }
    }
    return lines;
}

void print_lines(const vector<string> &lines)
{
    for (int i = 0; i < lines.size(); ++i)
    {
        cout << lines[i] << endl;
    }
}

struct Edge
{
    char left;
    char right;
    int weight;
    Edge(char left, char right, int weight)
    {
        this->left = left;
        this->right = right;
        this->weight = weight;
    }
    string to_str() const
    {
        string s = "";
        s += string(1, left) + " -- " + string(1, right) + ", weight = " + to_string(weight);
        return s;
    }

    bool operator== (const Edge &that) const
    {
        if(left == that.left && right == that.right)
            return true;
        else if (left == that.right && right == that.left)
            return true;
        else
            return false;
    }

    bool operator> (const Edge &that) const
    {
        if (this->weight > that.weight) return true;
        return false;
    }

    bool operator< (const Edge &that) const
    {
        if (this->weight < that.weight) return true;
        return false;
    }
    
    friend ostream & operator<< (ostream &os, const Edge &edge)
    {
        os << edge.left << " -- " << edge.right << ", weight = " << edge.weight;
        return os;
    }
};

vector<string> split(const string &line)
{
    vector<string> result;
    istringstream iss(line);

    do 
    {
        string item;
        iss >> item;
        result.push_back(item);
    }while(iss);
    return result;
}

template <typename T>
unordered_set<T> vector_to_set(const vector<T> &my_vector)
{
    unordered_set<T> result;
    for (int i = 0; i < my_vector.size(); ++i)
    {
        result.insert(my_vector[i]);
    }
    return result;
}

template <typename T>
vector<T> set_to_vector(const unordered_set<T> &set)
{
    vector<T> result;
    for (T element: set)
    {
        result.push_back(element);
    }
    return result;
}

vector<char> get_vertices(string inputFileName)
{
    vector<string> lines = get_lines(inputFileName);
    vector<char> vertices;
    for (int i = 0; i < lines.size(); ++i)
    {
        //cout << lines[i] << endl;
        vector<string> temp = split(lines[i]);
        int numberOfVertices = (temp.size()-1)/2;
        vertices.push_back(temp[0][0]);
        for (int j = 0; j < numberOfVertices; ++j)
        {
            vertices.push_back(temp[j+1][0]);
        }
    }
    //return vertices;
    return set_to_vector(vector_to_set(vertices));
}

vector<Edge> line_to_edge(const string &line)
{
    vector<Edge> edges;
    vector<string> elements = split(line);
    int numberOfEdges = (elements.size() - 1)/2;
    for (int i = 0; i < numberOfEdges; ++i)
    {
        Edge edge(elements[0][0], elements[i+1][0], stoi(elements[i + 1 + numberOfEdges]));
        edges.push_back(edge);
        //cout << edge.to_str() << endl;
    }
    return edges;
}

template <typename T>
bool contains(const vector<T> my_vector, T element)
{
    for (int i = 0; i < my_vector.size(); ++i)
    {
        if (my_vector[i] == element)
            return true;
    }
    return false;
}

/*unordered_map<char, vector<char> > generate_graph(string inputFileName)
{
    vector<string> lines = get_lines(inputFileName);
    unordered_map<char, vector<char> > graph;
    for (int i = 0; i < lines.size(); ++i)
    {
        vector<string> items = split(lines[i]);
        vector<char> adjacentVertices;
        int numberOfAdjacentVertices = (items.size() - 1)/2;
        for (int i = 0; i < numberOfAdjacentVertices; ++i)
        {
            adjacentVertices.push_back(items[i+1][0]);
        }
        graph[items[0][0]] = adjacentVertices;
    }
    return graph;
}*/

template <typename T>
priority_queue<T, vector<T>, greater<T> > vector_to_priority_queue(const vector<T> &my_vector)
{
    priority_queue<T, vector<T>, greater<T> > result;
    for (int i = 0; i < my_vector.size(); ++i)
    {
        result.push(my_vector[i]);
    }
    return result;
}

/*unordered_map<char, priority_queue<Edge, vector<Edge>, greater<Edge> > > generate_graph(string inputFileName)
{
    unordered_map<char, priority_queue<Edge, vector<Edge>, greater<Edge> > > graph;
    vector<string> lines = get_lines(inputFileName);
    for (int i = 0; i < lines.size(); ++i)
    {
        string line = lines[i];
        graph[line[0]] = vector_to_priority_queue(line_to_edge(line));
    }
    return graph;
}*/


/*unordered_map<char, vector<Edge> > generate_graph(string inputFileName)
{
    unordered_map<char, vector<Edge> > graph;
    vector<string> lines = get_lines(inputFileName);
    for (int i = 0; i < lines.size(); ++i)
    {
        string line = lines[i];
        graph[line[0]] = line_to_edge(line);
    }
    return graph;
}*/

unordered_map<char, vector<char> > generate_graph(string inputFileName)
{
    unordered_map<char, vector<char> > graph;
    vector<string> lines = get_lines(inputFileName);
    for (int i = 0; i < lines.size(); ++i)
    {
        string line = lines[i];
        vector<string> items = split(line);
        int numberOfAdjacentVertices = (items.size() - 1)/2;
        vector<char> adjacentVertices;
        for (int j = 0; j < numberOfAdjacentVertices; ++j)
        {
            adjacentVertices.push_back(items[j+1][0]);
        }
        graph[line[0]] = adjacentVertices;
    }
    return graph;
}

string vector_to_string(const vector<Edge> &my_vector)
{
    string result = "";
    for (int i = 0;  i < my_vector.size(); ++i)
    {
        result += my_vector[i].to_str() + "; ";
    }
    return result;
}

void print_graph(const unordered_map<char, vector<Edge> > &graph)
{
    for (pair<char, vector<Edge> > element: graph)
    {
        cout << element.first << " -> " << vector_to_string(element.second) << endl;
    }
}

/*string vector_to_string(const vector<char> &my_vector)
{
    string result = "";
    for (int i = 0; i < my_vector.size(); ++i)
    {
        result += string(1, my_vector[i]) + ", ";
    }
    return result;
}*/

/*void print_graph(const unordered_map<char, vector<char> > &graph)
{
    unordered_map<char, vector<char> >::iterator itr;
    for (itr = graph.begin(); itr != graph.end(); itr++)
    {
        cout << itr->first << " -> " << itr->second << endl;
    }
    for (pair<char, vector<char> >element: graph)
    {
        cout << element.first << " -> " << vector_to_string(element.second) << endl;
    }
}*/

vector<Edge> get_edges(string inputFileName)
{
    vector<string> lines = get_lines(inputFileName);
    vector<Edge> edges;
    for (int i = 0; i < lines.size(); ++i)
    {
        vector<Edge> temp = line_to_edge(lines[i]);
        for (int j = 0; j < temp.size(); ++j)
        {
            if (!contains(edges, temp[j]))
            {
                edges.push_back(temp[j]);
            }
        }
    }
    /*cout << "All edges: " << endl;
    for (int i = 0; i < edges.size(); ++i)
    {
        //cout << edges[i].to_str() << endl;
        cout << edges[i] << endl;
    }*/
    return edges;
}

template <typename T>
int find_index(const vector<T> &my_vector, T element)
{
    for (int i = 0; i < my_vector.size(); ++i)
    {
        if (my_vector[i] == element)
            return i;
    }
    return -1;
}

bool has_unvisited(const vector<bool> &visited)
{
    for (int i = 0; i < visited.size(); ++i)
    {
        if (!visited[i])
            return true;
    }
    return false;
}

template <typename T>
void print_pq(T &pq)
{
    while(!pq.empty())
    {
        cout << pq.top() << "; ";
        pq.pop();
    }
}

class Graph
{
    private:
        vector<char> vertices;
        vector<Edge> edges;
        //unordered_map<char, priority_queue<Edge, vector<Edge>, greater<Edge> > > graph;
        unordered_map<char, vector<char> > graph;
        vector<bool> visited;
    public:
        //Graph(){}
        Graph(string inputFileName)
        {
            this->graph = generate_graph(inputFileName);
            this->vertices = get_vertices(inputFileName);
            this->edges = get_edges(inputFileName);
            for (int i = 0; i < vertices.size(); ++i)
            {
                visited.push_back(false);
            }
        }

        vector<Edge> find_mst(char source)
        {
            assert(contains(this->vertices, source));
            vector<Edge> tree;
            char current_vertex = source;
            int current_index = find_index(this->vertices, source);
            visited[current_index] = true;
            queue<char> q;
            q.push(source);
            while(!q.empty())
            {
                current_vertex = q.front();
                cout << "Current_vertex: " << current_vertex << endl;
                current_index = find_index(vertices, current_vertex);
                assert(current_index >= 0 && current_index < vertices.size());
                cout << "Current_index: " << current_index << endl;
                assert(current_index >= 0);
                visited[current_index] = true;
                vector<char> adjacentVertices = graph[current_vertex];
                for (int i = 0; i < adjacentVertices.size(); ++i)
                {
                    if (!visited[find_index(this->vertices, adjacentVertices[i])])
                    {
                        q.push(adjacentVertices[i]);
                    }
                }
                for (char ele: adjacentVertices)
                {
                    cout << ele << ", ";
                }
                cout << endl;
                vector<Edge> adjacentEdges;
                for (int i = 0; i < adjacentVertices.size(); ++i)
                {
                    char temp_vertex = adjacentVertices[i];
                    int temp_index = find_index(vertices, temp_vertex);
                    assert(temp_index >= 0);
                    //cout << temp_vertex << ", " << temp_index << endl;
                    if (true)
                    {
                        Edge edge(current_vertex, temp_vertex, 0);
                        int edge_index = find_index(this->edges, edge);
                        /*cout << edge << endl;
                        cout << "All edges: " << endl;
                        for (Edge ele: edges)
                        {
                            cout << ele << endl;
                        }
                        cout << "edge_index: " << edge_index << endl;*/
                        assert(edge_index >= 0 && edge_index < edges.size());
                        adjacentEdges.push_back(this->edges[edge_index]);
                    }
                }
                cout << "All adjacent edges: " << endl;
                for (Edge ele: adjacentEdges)
                {
                    cout << ele << endl;
                }
                if(adjacentEdges.size() == 0)
                {
                    q.pop();
                }
                else
                {
                    int min_weight = adjacentEdges[0].weight;
                    int min_index = 0;
                    for (int i = 0; i < adjacentEdges.size(); ++i)
                    {
                        if (min_weight > adjacentEdges[i].weight)
                        {
                            min_weight = adjacentEdges[i].weight;
                            min_index = i;
                        }
                    }
                    tree.push_back(adjacentEdges[min_index]);
                    Edge min_edge = adjacentEdges[min_index];
                    cout << "min_edge: " << endl;
                    cout << min_edge << endl;
                    if (current_vertex == min_edge.left)
                    {
                        //q.push(min_edge.right);
                        visited[find_index(vertices, min_edge.right)] = true;
                    }
                    else if (current_index == min_edge.right)
                    {
                        //q.push(min_edge.left);
                        visited[find_index(vertices, min_edge.left)] = true;
                    }
                    else
                    {
                        cout << "Error in the min_edge for vertex " << current_vertex << endl;
                        exit(-1);
                    }
                    q.pop();
                }
            }
            return tree;
        }

        void bfs(char source)
        {
            assert(contains(vertices, source));
            queue<char> q;
            q.push(source);
            visited[find_index(vertices, source)] = true; 
            while(!q.empty())
            {
                char current_vertex = q.front();
                visited[find_index(vertices, current_vertex)] = true;
                cout << current_vertex << endl;
                vector<char> adjacentVertices = graph[current_vertex];
                for (int i = 0; i < adjacentVertices.size(); ++i)
                {
                    char temp_vertex = adjacentVertices[i];
                    if (!visited[find_index(vertices, temp_vertex)])
                    {
                        q.push(temp_vertex);
                    }
                }
                q.pop();
            }
        }

        /*~Graph()
        {
            for (pair<char, priority_queue<Edge, vector<Edge>, greater<Edge> > > ele: graph)
            {
                cout << ele.first << " -> ";
                print_pq(ele.second); 
                cout << endl;
            }
        }*/
};

int main()
{
    string inputFileName = "graph.txt";
    Graph graph = Graph(inputFileName);
    //vector<Edge> tree = graph.find_mst('a');
    graph.bfs('a');
    return 0;
}
