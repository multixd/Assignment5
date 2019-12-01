//
//  graph.cpp
//  Assignment5
//
//  Created by Vincent Liang on 11/29/19.
//  Copyright © 2019 Vincent Liang. All rights reserved.
//

#include "graph.h"
int factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

vector<string>* Node::neighbors() {
    vector<string>* vec = new vector<string>();
    vector<Edge*>::iterator it;

    for(it=adjacents->begin();it!=adjacents->end();it++) {
        vec->push_back((*it)->getNode()->getPayload());
    }

    return vec;
}

bool Node::isConnected(Node* n) const{
    for(int i = 0;i<this->degree(); ++i) {
        if(this->adjacents->at(i)->getNode() ==  n) {
            return  true;
        }
    }
    return false;
}

void Graph::addNode(string name) {
    Node* node = new Node(name);
    graph->insert(pair<string,Node*>(name,node));
}

void Graph::addEdge(string k1, string k2, double w=1.0) {
    map<string,Node* >::iterator it1,it2;
    it1 = graph->find(k1);
    it2 = graph->find(k2);

   //Check both nodes exists using the map
    if (it1 != graph->end() && it2 != graph->end()) {
        Node* n1 = (*it1).second;
        Node* n2 = (*it2).second;
        //Create the edge and add it to the adjacents
        Edge* e = new Edge(n2,w);
        n1->addEdge(e);
        //Undirected graph: we add the reverse or back edge
    if (!directed) {
        Edge* be = new Edge(n1,w);
        n2->addEdge(be);
      }
   }
 }


void Graph::printGraph() {
    //Iterate each node
    map<string,Node* >::iterator it;
    for (it=graph->begin(); it != graph->end();it++) {
        Node* n = (*it).second;
        cout << n->getPayload() << "[";

        //Iterate the neighboors
        vector<string>* neigh  = n->neighbors();
        vector<string>::iterator itn;
        
        for(itn=neigh->begin();itn!=neigh->end();itn++) {
           cout << (*itn) << " ";
        }
        
        cout << "]" << endl;
    }
}

bool Graph::IsThereTripletClique(){
    vector<Node*> aja;
    map<string,Node* >::iterator it;
    for(it=graph->begin(); it != graph->end();it++) {
        Node* n = (*it).second;
        if(n->degree() > 1) {
            for(int i = 0; i < n->degree(); ++i) {
                aja.push_back(n->adjacentsList()->at(i)->getNode());
            }
//            for(int j = 0;  j<aja.size();++j)  {
//                cout << aja.at(j)  <<  " ";
//            }
//            cout << endl << endl;
            for(int i = 0; i<aja.size()-1;++i) {
                for(int j=i+1; j<aja.size();++j) {
                    if(aja.at(i)->isConnected(aja.at(j))) {
//                        cout << n->getPayload() << " " << aja.at(i)->getPayload() << " " <<aja.at(j) -> getPayload();
                        return true;
                    }
                }
            }
        }
        aja.clear();
    }
    
    return false;
}

double Graph::GetMinDistance(string city1,string city2){
    map<string,Node* >::iterator it;
    map<string,unsigned int> dist;
    vector<string> nodes;
    
    for (it=graph->begin(); it != graph->end();it++) {
        string name = (*it).second->getPayload();
        nodes.push_back(name);
        if(name==city1){
            dist.insert(pair<string,unsigned int>(name,0));
        }
        else{
            dist.insert(pair<string,unsigned int>(name,-1));
        }
    }
    
    map<string,unsigned int>::iterator i;
    string num;
    unsigned int min = -1;
    
    
    while(!nodes.empty()){
        for(i=dist.begin();i!=dist.end();++i){
            if(i->second < min){
                min = i->second;
                num = i->first;
            }
        }
        vector<string>::iterator iy;
        for(iy= nodes.begin();iy!=nodes.end();++iy) {
            if(*iy==num) {
                nodes.erase(iy);
                break;
            }
        }
        
        vector<Edge*> *adj = (graph->find(num))->second->adjacentsList();
    
        for(int i = 0; i<adj->size();++i){
            double weight = (dist.find(adj->at(i)->getNode()->getPayload()))->second;
            double alternative =adj->at(i)->getWeight()+ (dist.find(num))->second;
            if(alternative < weight){
                (dist.find(adj->at(i)->getNode()->getPayload()))->second = alternative;
            }
        }
        num = nullptr;
        min = -1;
    }
    return  dist.find(city2)->second;
}

int main() {
    cout << "Graph Example 2.0\n";
    Graph g(false);

    g.addNode("a");
    g.addNode("b");
    g.addNode("c");

    g.addEdge("a","b",10);
    g.addEdge("b","c",5);
    g.addEdge("c","a",9);
    if(g.IsThereTripletClique()) {
        cout << "Yes" ;
    }

    //g.printGraph();

}
