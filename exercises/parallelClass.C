#include "parallelClass.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool Foam::parallelClass::next(label n, label& i) const
{
    bool res;
    label rangeMax = int(std::sqrt(n))+1;

    // moves i to next possible divisor in local process range;
    // which is a "contagious" portion of (3, n)
    // and it's the whole (3, n) range in serial

    if (Pstream::parRun()) {
        label start = 3+Pstream::myProcNo();
        
        if (i < start) {
            i = start;
            res = true;
        } else if (i <= rangeMax) {
            i += Pstream::nProcs();
            res = true;
        }

        if (i >= rangeMax) res = false;
    } else {
        if (i<2) {
            i = 2;
            res = true;
        } else if (i <= rangeMax) {
            i++;
            res = true;
        }
        if (i>rangeMax) res = false;
    }

    return res;
}

bool Foam::parallelClass::isPrime(label n) const
{
    // This function must return:
    // true if n is a prime number
    // false otherwise

    if (n == 2) return true;
    if (n % 2 == 0) return false;

    // This is serial code, use P2P comms to distribute the work
    bool res = true;

    // last possible divisor
    label rangeMax = int(std::sqrt(n))+1;
    for(label i = next(n,i) ; next(n, i); )
    {
        if (n % i == 0) {
            res = false;
            break;
        }
    }

    reduce(res, andOp<bool>());
    
    return res;
}

}
// ************************************************************************* //
