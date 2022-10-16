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
        mesh_(mesh)
    {};
    parallelClass(parallelClass &&) = default;
    parallelClass(const parallelClass &) = default;
    // Assignment/Move operators
    parallelClass &operator=(parallelClass &&) = default;
    parallelClass &operator=(const parallelClass &) = default;
    // Destructor
    ~parallelClass() {};

    // Member methods
    bool checkPosition(const vector&) const;
    label whoHasReferenceCell(const vector&) const;

protected:
    // Member variables
    const fvMesh& mesh_;
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
