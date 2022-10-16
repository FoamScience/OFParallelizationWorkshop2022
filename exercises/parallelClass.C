#include "parallelClass.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Ostream&  operator<<(Ostream& os, const Edge& e) {
    os << e.destination << " " << e.weight;
    return os;
}

Istream&  operator>>(Istream& is, Edge& e) {
    is >> e.destination;
    is >> e.weight;
    return is;
}

List<List<Edge>> Edge::collectEdges(const fvMesh& mesh) {
        List<List<Edge>> g(Pstream::nProcs());
        forAll(mesh.boundaryMesh(), pi) {
            const auto* patch = dynamic_cast<const processorPolyPatch*>(&mesh.boundaryMesh()[pi]);
            if (patch) {
                Edge e(patch->neighbProcNo(), 0);
                g[Pstream::myProcNo()].append(e);
            }
        }
        Pstream::gatherList(g);
        Pstream::scatterList(g);
        return g;
}

}
// ************************************************************************* //
