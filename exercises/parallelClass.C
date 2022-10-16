#include "parallelClass.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Ostream&  operator<<(Ostream& os, const Edge& e) {
    os  << labelList(1, e.destination) << nl;
    return os;
}

Istream&  operator>>(Istream& is, Edge& e) {
    List<label> tmp(is);
    e.destination = tmp[0];
    return is;
}

List<IDLList<Edge>> Edge::collectEdges(const fvMesh& mesh) {
    List<IDLList<Edge>> graph;
    IDLList<Edge> g;

    forAll(mesh.boundaryMesh(), pi) {
        const auto* patch = dynamic_cast<const processorPolyPatch*>(&mesh.boundaryMesh()[pi]);
        if (patch) {
            Edge e(mesh, patch->neighbProcNo());
            g.append(e.clone().ptr());
        }
    }
    
    if (Pstream::master()) {
        graph.append(g);
        for(label i = Pstream::firstSlave(); i<=Pstream::lastSlave(); i++ ) {
            IPstream fromSlave(Pstream::blocking, i);
            IDLList<Edge> es(fromSlave,Edge::iNew(mesh));
            graph.append(es);
        }
    } else {
        OPstream toMaster(Pstream::blocking, Pstream::masterNo());
        toMaster << g;
    }

    return graph;
}

}
// ************************************************************************* //
