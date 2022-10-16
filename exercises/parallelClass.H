#ifndef parallelClass_H
#define parallelClass_H

#include "Pstream.H"
#include "labelList.H"
#include "fvMesh.H"
#include "processorPolyPatch.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class Edge;

Ostream& operator<<(Ostream& os, const Edge& e);
Istream& operator>>(Istream& os, Edge& e);

struct Edge;
Istream&  operator>>(Istream& is, Edge& e);

struct Edge {
    // Constructors
    Edge() {};
    Edge(const label& d, const scalar& s) : destination(d), weight(s) {};

    // Member operators
    bool operator==(const Edge& ej) const {
        return destination == ej.destination;
    }
    bool operator!=(const Edge& ej) const {
        return destination != ej.destination;
    }

    // Build a graph of edges "between processes"
    static List<List<Edge>> collectEdges(const fvMesh&);

    // Member methods
    label destination;
    scalar weight;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
