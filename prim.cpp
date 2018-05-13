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

template <typename T>
void print_vector(const vector<T> &my_vector)
{
    for (int i = 0; i < my_vector.size(); ++i)
    {
        cout << my_vector[i] << ", ";
    }
    cout << endl;
}

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

struct Vertex
{
    char vertex;
    int color;
    Vertex()
    {
        this->vertex = '0';
        this->color = -1;
    }
    Vertex(char vertex, int color)
    {
        this->vertex = vertex;
        this->color = color;
    }
    Vertex(const Vertex &parameter)
    {
        this->vertex = parameter.vertex;
        this->color = parameter.color;
    }
    void set_color(int color)
    {
        assert(color == 0 || color == 1 || color == 2);
        this->color = color;
    }
    bool operator== (const Vertex &that) const
    {
        return this->vertex == that.vertex;
    }
    const Vertex & operator= (const Vertex &that)
    {
        this->vertex = that.vertex;
        this->color = that.color;
        return *this;
    }
    string to_str() const
    {
        return string(1, this->vertex) + ", color = " + to_string(this->color);
    }
    friend ostream & operator<< (ostream &os, const Vertex &parameter)
    {
        os << parameter.vertex << ", color = " << parameter.color;
        return os;
    }
};

struct Edge
{
    Vertex left;
    Vertex right;
    int weight;
    Edge(Vertex left, Vertex right, int weight)
    {
        this->left = left;
        this->right = right;
        this->weight = weight;
    }
    string to_str() const
    {
        string s = "";
        s += left.to_str() + " -- " + right.to_str() + ", weight = " + to_string(weight);
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

vector<Vertex> get_vertices(string inputFileName)
{
    vector<string> lines = get_lines(inputFileName);
    vector<Vertex> vertices;
    unordered_set<char> vertex_set;
    for (int i = 0; i < lines.size(); ++i)
    {
        //cout << lines[i] << endl;
        vector<string> temp = split(lines[i]);
        int numberOfVertices = (temp.size()-1)/2;
        vertex_set.insert(temp[0][0]);
        for (int j = 0; j < numberOfVertices; ++j)
        {
            vertex_set.insert(temp[j+1][0]);
        }
    }
    for (auto ele: vertex_set)
    {
        vertices.push_back(Vertex(ele, 0));
    }
    return vertices;
}

vector<Edge> line_to_edge(const string &line)
{
    vector<Edge> edges;
    vector<string> elements = split(line);
    int numberOfEdges = (elements.size() - 1)/2;
    for (int i = 0; i < numberOfEdges; ++i)
    {
        Edge edge(Vertex(elements[0][0], 0), Vertex(elements[i+1][0], 0), stoi(elements[i + 1 + numberOfEdges]));
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

unordered_map<char, vector<Vertex> > generate_graph(string inputFileName)
{
    unordered_map<char, vector<Vertex> > graph;
    vector<string> lines = get_lines(inputFileName);
    for (int i = 0; i < lines.size(); ++i)
    {
        string line = lines[i];
        vector<string> items = split(line);
        int numberOfAdjacentVertices = (items.size() - 1)/2;
        vector<Vertex> adjacentVertices;
        for (int j = 0; j < numberOfAdjacentVertices; ++j)
        {
            adjacentVertices.push_back(Vertex(items[j+1][0], 0));
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
        vector<Vertex> vertices;
        vector<Edge> edges;
        //unordered_map<char, priority_queue<Edge, vector<Edge>, greater<Edge> > > graph;
        unordered_map<char, vector<Vertex> > graph;
    public:
        //Graph(){}
        Graph(string inputFileName)
        {
            this->graph = generate_graph(inputFileName);
            this->vertices = get_vertices(inputFileName);
            this->edges = get_edges(inputFileName);
            /*for (auto vertex: vertices)
            {
                cout << vertex << endl;
            }
            for (auto edge: edges)
            {
                cout << edge << endl;
            }
            for (auto pair: graph)
            {
                char vertex = pair.first;
                vector<Vertex> adjacentVertices = pair.second;
                cout << string(1, vertex) + " -> ";
                for (auto ele: adjacentVertices)
                {
                    cout << ele << "; ";
                }
                cout << endl;
            }*/
        }

        vector<Vertex *> find_adjacent_vertices(Vertex *source)
        {
            vector<Vertex> adjacentVertices = graph[source->vertex];
            vector<int> adjacentIndices;
            for (auto vertex: adjacentVertices)
            {
                adjacentIndices.push_back(find_index(this->vertices, vertex));
            }
            vector<Vertex *> result;
            for (int index: adjacentIndices)
            {
                result.push_back(&vertices[index]);
            }
            return result;
        }

        vector<Vertex *> find_adjacent_unvisited_vertices(Vertex *source)
        {
            vector<Vertex> adjacentVertices = graph[source->vertex];
            vector<int> adjacentIndices;
            for (auto ele: adjacentVertices)
            {
                adjacentIndices.push_back(find_index(this->vertices, ele));
            }
            vector<Vertex *> adjacentUnvisitedVertices;
            for (auto index: adjacentIndices)
            {
                if (vertices[index].color == 0)
                {
                    adjacentUnvisitedVertices.push_back(&vertices[index]);
                }
            }
            return adjacentUnvisitedVertices;
        }

        vector<Edge *> find_adjacent_unvisited_edges(Vertex *source)
        {
            vector<Vertex *> adjacentUnvisitedVertices = find_adjacent_unvisited_vertices(source);
            vector<Edge *> adjacentUnvisitedEdges;
            for (Vertex * vertex: adjacentUnvisitedVertices)
            {
                Edge edge = Edge(*source, *vertex, 0);
                int edge_index = find_index(edges, edge);
                adjacentUnvisitedEdges.push_back(&edges[edge_index]);
            }
            return adjacentUnvisitedEdges;
        }

        int get_weight(const Vertex &a, const Vertex &b)
        {
            Edge edge = Edge(a, b, 0);
            for (int i = 0; i < edges.size(); ++i)
            {
                if (edge == edges[i])
                    return edges[i].weight;
            }
            return -1;
        }

        vector<Edge> get_tree_adjacent_edges(const vector<Vertex> &inside, const vector<Vertex> &outside)
        {
            vector<Edge> result;
            assert(inside.size() + outside.size() == vertices.size());
            for (int i = 0; i < inside.size(); ++i)
            {
                vector<Vertex> adjacentVertices = graph[inside[i].vertex];
                for (auto vertex: adjacentVertices)
                {
                    if (contains(outside, vertex))
                    {
                        Edge edge(inside[i], vertex, 0);
                        int edge_index = find_index(edges, edge);
                        if (!contains(result, edges[edge_index]))
                            result.push_back(edges[edge_index]);
                    }
                }
            }
            return result;
        }

        vector<Edge> find_mst()
        {
            vector<Edge> tree;
            vector<Vertex> inside;
            vector<Vertex> outside;
            for (int i = 0; i < vertices.size(); ++i)
            {
                outside.push_back(vertices[i]);
            }
            for (int i = 0; i < outside.size(); ++i)
            {
                cout << outside[i] << ", ";
            }
            cout << endl;
            inside.push_back(outside.front());
            outside.erase(outside.begin());
            while(!outside.empty())
            {
                //cout << "Number of outside vertices = " << outside.size() << endl;
                cout << "Inside vertices: " << endl;
                print_vector(inside);
                cout << "Outside vertices: " << endl;
                print_vector(outside);
                vector<Edge> tree_adjacent_edges = get_tree_adjacent_edges(inside, outside);
                cout << "Adjacent edges of current tree: " << endl;
                for (int i = 0; i < tree_adjacent_edges.size(); ++i)
                {
                    cout << tree_adjacent_edges[i] << endl;
                }
                if (tree_adjacent_edges.size() == 0)
                {
                    outside.erase(outside.begin());
                    break;
                }
                else
                {
                    int min_weight = tree_adjacent_edges[0].weight;
                    int min_index = 0;
                    for (int i = 1; i < tree_adjacent_edges.size(); ++i)
                    {
                        Edge edge = tree_adjacent_edges[i];
                        if (edge.weight < min_weight)
                        {
                            min_weight = edge.weight;
                            min_index = i;
                        }
                    }
                    Edge min_edge = tree_adjacent_edges[min_index];
                    tree.push_back(min_edge);
                    cout << "min_edge to be added to the tree: " << min_edge << endl;
                    bool add_left;
                    if (contains(inside, min_edge.left))
                    {
                        assert(!contains(inside, min_edge.right));
                        inside.push_back(min_edge.right);
                        add_left = false;
                    }
                    else
                    {
                        assert(!contains(inside, min_edge.left));
                        inside.push_back(min_edge.left);
                        add_left = true;
                    }
                    if (add_left)
                        outside.erase(outside.begin() + find_index(outside, min_edge.left));
                    else
                        outside.erase(outside.begin() + find_index(outside, min_edge.right));
                }
            }
            return tree;
        }
       
        void bfs(Vertex source)
        {
            assert(contains(vertices, source));
            int source_index = find_index(vertices, source);
            assert(vertices[source_index].color == 0);
            queue<Vertex *> q;
            q.push(&vertices[source_index]);
            q.front()->color = 1;
            while(!q.empty())
            {
                Vertex * temp = q.front();
                cout << *temp << endl;
                temp->color = 2;
                vector<Vertex *> adjacentVertices = find_adjacent_vertices(temp);
                for (auto ele: adjacentVertices)
                {
                    if (ele->color == 0)
                    {
                        q.push(ele);
                        ele->color = 1;
                    }
                }
                q.pop();
            }
            /*cout << "Updated vertices: " << endl;
            for (auto ele: vertices)
            {
                cout << ele << endl;
            }*/
        }
};

int main()
{
    string inputFileName = "graph.txt";
    Graph graph = Graph(inputFileName);
    vector<Edge> tree = graph.find_mst();
    cout << "The minimum spanning tree: " << endl;
    for (auto edge: tree)
    {
        cout << edge << endl;
    }
    //graph.bfs(Vertex('a', 0));
    return 0;
}
