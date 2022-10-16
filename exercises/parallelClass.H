#ifndef parallelClass_H
#define parallelClass_H

#include "Pstream.H"
#include "IDLList.H"
#include "fvMesh.H"
#include "processorPolyPatch.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class Edge;

Ostream& operator<<(Ostream& os, const Edge& e);
Istream& operator>>(Istream& is, Edge& e);

struct Edge;
Istream&  operator>>(Istream& is, Edge& e);

struct Edge 
    : public IDLList<Edge>::link
{
    // Constructors
    Edge(const fvMesh& mesh, label dest)
        : IDLList<Edge>::link(), destination(dest), mesh(mesh) {};
    Edge(const fvMesh& mesh, Istream& is)
        : IDLList<Edge>::link(), destination(0), mesh(mesh)
    {
        operator>>(is, *this);
    };
    Edge(const Edge& e)
        : IDLList<Edge>::link(), destination(e.destination), mesh(e.mesh)
    {};

    //- Clone
    autoPtr<Edge> clone() const
    {
        return autoPtr<Edge>(new Edge(*this));
    }

    // Member operators
    bool operator==(const Edge& ej) const {
        return destination == ej.destination;
    }
    bool operator!=(const Edge& ej) const {
        return destination != ej.destination;
    }

    // Build a graph of edges "between processes"
    static List<IDLList<Edge>> collectEdges(const fvMesh&);

    // Member methods
    label destination;
    const fvMesh& mesh;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
