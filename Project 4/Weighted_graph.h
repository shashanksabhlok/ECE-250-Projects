#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <iostream>
#include <limits>
#include "Exception.h"

/*****************************************
 * UW User ID:  ssabhlok
 * Submitted for ECE 250
 * Semester of Submission:  (Fall) 2014
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

class Weighted_graph {
	private:
		static const double INF;
		double**graph_matrix;
		int	*degreecounter;
		int verticesNumber;
		int	edgesNumber;


	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double minimum_spanning_tree( int ) const;
		bool is_connected() const;
	    void bfs(bool*,int) const;

		void insert( int, int, double );

	// Friends

	friend std::ostream &operator << ( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// Enter definitions for all public functions here

// Constructs a new Weighted Graph Object
Weighted_graph :: Weighted_graph (int n)
{
	graph_matrix = new double * [n];
	degreecounter = new int [n];

	for (int i = 0; i < n; i ++)
	{
		graph_matrix [i] = new double [n];
	}
	
	for (int i = 0; i < n; i ++)
	{
		//degreecounter = new int [n];
		for (int j = 0; j < n; j ++ )
		{
			graph_matrix [i][j] = INF;
		}
		graph_matrix [i][i] = 0;
	}
	verticesNumber = n;
	edgesNumber = 0;
}
// Destructor for the MST generated
Weighted_graph :: ~Weighted_graph()
{
	for (int i=0; i <verticesNumber; i ++)
	{
		delete[] graph_matrix [i];
	}

	delete[] graph_matrix;
	delete[] degreecounter;
}

int Weighted_graph :: degree (int n) const
{
	if (n >= verticesNumber)
	{
		throw illegal_argument();
	}

	if (n < 0)
	{
		throw illegal_argument();
	}

	return degreecounter[n];
}

int Weighted_graph :: edge_count () const
{
	return edgesNumber;
}

double Weighted_graph :: adjacent (int m, int n) const
{
	if(m >= verticesNumber || n >= verticesNumber)
	   {
		 throw illegal_argument();
	   }
	if (m < 0 || n < 0)
	{
		throw illegal_argument();
	}

	if (m == n)
	{
		return 0;
	}


	return graph_matrix [m][n];
	
}

// Inserts a new edge between the nodes n  & m with weight w
void Weighted_graph :: insert (int m, int n,double w) 
{
	if(m >= verticesNumber || n >= verticesNumber)
		{
			throw illegal_argument();
		}
	if (m < 0 || n < 0)
		{
			throw illegal_argument();
		}

	if (m == n)
		{
			throw illegal_argument();
		}

	if (w < 0 || w == INF)
		{
			throw illegal_argument();
		}

	if (graph_matrix[m][n] != INF && w!=0)
	{		
			graph_matrix[m][n] = w;
			graph_matrix[n][m] = w;
	}

	else if ( w == 0 && (graph_matrix[m][n] !=INF))
	{
			graph_matrix[m][n] = INF;
			graph_matrix[n][m] = INF;
			edgesNumber = edgesNumber - 1;
			degreecounter[m] =degreecounter[m]  - 1;
			degreecounter[n] = degreecounter[n] - 1;

	}
	else if (graph_matrix[m][n] == INF & w!=0)
		{
			graph_matrix[m][n] = w;
			graph_matrix[n][m] = w;
			edgesNumber = edgesNumber +1;
			degreecounter[m] = degreecounter[m] + 1;
			degreecounter[n] = degreecounter[n] +1;
		}

}

// Uses the Prim-Jarnik Algorithm to form an MST Tree
double Weighted_graph ::minimum_spanning_tree(int r) const
{
	double *weight  = new double [verticesNumber];
	double sum = 0;
	double min;
	int   minIndex;
	int current = r;
	bool *visited =  new bool [verticesNumber];

	if( r < 0 || r > (verticesNumber - 1))
	{
		delete [] weight;
		delete [] visited;
		throw illegal_argument();
	}
	for(int i = 0; i < verticesNumber; i++) {
		weight[i] = INF;
		visited[i] = false;
	}

	for ( int i =0; i < verticesNumber ; i++)
	{		
		visited [current] = true;
		
		for (int j = 0; j < verticesNumber; j ++)
		{
			if ( graph_matrix[current][j] < weight[j])
			{
			 weight[j] = graph_matrix [current][j];
			}
		}
	
	min = INF;
	for (int k = 0; k < verticesNumber; k++)
	{
		if (visited[k] == false)
		{
			if( weight[k] < min )
			{
				min = weight[k];
				minIndex = k;
			}
			
		}
	}
	if(min == INF)
	{
		delete[] weight;
		delete[] visited;
		return sum;
	}
	else {
		sum = sum + min;
		current = minIndex;
	}
  }
	delete[] weight;
	delete[] visited;
	return sum;
}

// Checks if the graph is connected or if it contains disconnected components
// Employs the BFS Algorithm
 bool Weighted_graph :: is_connected() const
{
	bool *visited = new bool [verticesNumber];
	
	for(int i = 0; i < verticesNumber; i++)
		visited[i] = false;

	bfs(visited,0);
	for ( int i =0; i < verticesNumber; i++)
	{
		if (visited[i] == false)
		{
			delete[] visited;
			return false;
		}
			
	}
	delete[] visited;
	return true;
}

 // The BFS Algorithm for spanning the MST.
void Weighted_graph :: bfs(bool* v,int current) const
{
	v[current] = true;
	for (int i = 0 ; i < verticesNumber; i++)
	{
		if (graph_matrix [current][i] != INF && v[i] == false)
		{
			bfs(v, i);
		}
	}
	
}




std::ostream &operator << ( std::ostream &out, Weighted_graph const &graph ) {
	// Your implementation

	return out;
}

#endif