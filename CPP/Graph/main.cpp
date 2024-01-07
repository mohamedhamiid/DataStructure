#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int, string> Vertex;
typedef pair<int, Vertex> Cost_Adjacent;
typedef vector<Cost_Adjacent> Edges;
/* Graph */
class Graph
{
private:
    typedef pair<int, int> EdgeInIndex;
    typedef vector<EdgeInIndex> EdgesInIndex;
    vector<pair<Vertex, EdgesInIndex>> element;

public:
    int noOfVertices = 0;
    void insertVertex(Vertex vertex, Edges edge)
    {

        EdgesInIndex indeces;
        for (int i = 0; i < edge.size(); i++)
        {
            indeces.push_back(make_pair(edge[i].first, edge[i].second.first));
            cout << indeces[i].first << " " << indeces[i].second << endl;
        }
        cout << endl;
        element.push_back(make_pair(vertex, indeces));

        noOfVertices++;
    }
    int MST_prim(int sourceIndex, Graph *graph)
    {
        priority_queue<EdgeInIndex, vector<EdgeInIndex>, greater<EdgeInIndex>> q;
        q.push(make_pair(0, sourceIndex));

        vector<bool> added(graph->noOfVertices, false);

        int MST_cost = 0;
        while (!q.empty())
        {
            EdgeInIndex least;
            least = q.top();
            q.pop();

            int cost = least.first;
            int node = least.second;
            cout << cost << " " << node << endl;

            if (!added[node])
            {
                MST_cost += cost;
                added[node] = true;

                for (int i = 0; i < graph->element[node].second.size(); i++)
                {
                    int adj_node = (element[node].second)[i].second;
                    if (added[adj_node] == false)
                    {
                        q.push(element[node].second[i]);
                    }
                }
            }
        }
        return MST_cost;
    }
    int MST_kruskal(int sourceIndex, Graph *graph)
    {
        priority_queue<EdgeInIndex, vector<EdgeInIndex>, greater<EdgeInIndex>> q;
        q.push(make_pair(0, sourceIndex));

        vector<bool> added(graph->noOfVertices, false);

        int MST_cost = 0;
        while (!q.empty())
        {
            EdgeInIndex least;
            least = q.top();
            q.pop();

            int cost = least.first;
            int node = least.second;
            cout << cost << " " << node << endl;

            if (!added[node])
            {
                MST_cost += cost;
                added[node] = true;

                for (int i = 0; i < graph->element[node].second.size(); i++)
                {
                    int adj_node = (element[node].second)[i].second;
                    if (added[adj_node] == false)
                    {
                        q.push(element[node].second[i]);
                    }
                }
            }
        }
        return MST_cost;
    }
};

int main()
{
    Graph g1;
    Vertex a, b, c, d, e, f, g;
    a = {0, "A"};
    b = {1, "B"};
    c = {2, "C"};
    d = {3, "D"};
    e = {4, "E"};
    f = {5, "F"};
    g = {6, "G"};
    g1.insertVertex(a,
                    {{1, b},
                     {2, c},
                     {1, d},
                     {1, e},
                     {2, f},
                     {1, g}});

    g1.insertVertex(b,
                    {{1, a},
                     {2, c},
                     {2, g}});

    g1.insertVertex(c,
                    {{2, a},
                     {2, b},
                     {1, d}});
    g1.insertVertex(d,
                    {{1, a},
                     {1, c},
                     {1, e}});
    g1.insertVertex(e,
                    {{1, a},
                     {1, d},
                     {2, f}});
    g1.insertVertex(f,
                    {{2, a},
                     {2, e},
                     {1, g}});
    g1.insertVertex(g,
                    {{1, a},
                     {1, f},
                     {2, b}});

    cout << g1.noOfVertices << endl;
    cout << g1.MST_prim(0, &g1);
}