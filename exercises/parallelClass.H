#ifndef parallelClass_H
#define parallelClass_H

#include "Pstream.H"
#include "labelList.H"
#include "fvMesh.H"
#include "processorPolyPatch.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class parallelClass
{
public:
    // Constructors
    parallelClass(const fvMesh& mesh)
    :
        lists_(Pstream::nProcs()),
        mesh_(mesh)
    {
        const auto& patches = mesh.boundaryMesh();
        forAll(patches, patchi)
        {
            const auto *p = dynamic_cast<processorPolyPatch const*>(&patches[patchi]);
            if (p) {
                lists_[p->neighbProcNo()] = labelList(p->size(), Pstream::myProcNo());
            }
        }
    };
    parallelClass(parallelClass &&) = default;
    parallelClass(const parallelClass &) = default;
    // Assignment/Move operators
    parallelClass &operator=(parallelClass &&) = default;
    parallelClass &operator=(const parallelClass &) = default;
    // Destructor
    ~parallelClass() {};

    // Member methods
    // Swap lists between neighbouring processors
    void swapLists();
    // Return list at index proc on local process
    const labelList& list(label proc) const {
        return lists_[proc];
    }
    // Return a list of IDs for neighbouring processes
    labelList neis() const {
        const auto& patches = mesh_.boundaryMesh();
        labelList ns;
        forAll(patches, patchi)
        {
            const auto *p = dynamic_cast<processorPolyPatch const*>(&patches[patchi]);
            if (p) {
                ns.append(p->neighbProcNo());
            }
        }
        return ns;
    }

protected:
    // Member variables
	List<labelList> lists_;
    const fvMesh& mesh_;
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
