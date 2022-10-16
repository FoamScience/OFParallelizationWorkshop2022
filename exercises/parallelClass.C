#include "parallelClass.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Ostream&  operator<<(Ostream& os, const Edge& e) {
    return os;
}

Istream&  operator>>(Istream& is, Edge& e) {
    return is;
}

List<IDLList<Edge>> Edge::collectEdges(const fvMesh& mesh) {
    List<IDLList<Edge>> graph;

    return graph;
}

}
// ************************************************************************* //
