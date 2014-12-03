#include <iostream>
#include <seqan/align.h>

using namespace seqan;

void basic() {

    typedef String<char> TSequence;
    typedef Align<TSequence, ArrayGaps> TAlign;
    typedef Row<TAlign>::Type TRow;

    TSequence seq1 = "CDFGDC";
    TSequence seq2 = "CDEFGAHGC";

    TAlign align;
    resize(rows(align), 2);
    assignSource(row(align, 0), seq1);
    assignSource(row(align, 1), seq2);

    std::cout << align;

    TRow &row1 = row(align, 0);
    TRow &row2 = row(align, 1);

    insertGap(row1, 2);
    std::cout << align;
    insertGaps(row1, 5, 2);

    std::cout << align;


    std::cout << "\nViewToSource1: ";
    for (unsigned i(0); i < length(row1); ++i)
        std::cout << toSourcePosition(row1, i) << ",";

    std::cout << "\nViewToSource2: ";
    for (unsigned i(0); i < length(row2); ++i) 
        std::cout << toSourcePosition(row2, i) << ",";
    std::cout << "\n";


    std::cout << "\nSourceToView1: ";
    for (unsigned i(0); i < length(source(row1)); ++i)
        std::cout << toViewPosition(row1, i) << ",";

    std::cout << "\nSourceToView2: ";
    for (unsigned i(0); i < length(source(row2)); ++i)
        std::cout << toViewPosition(row2, i) << ",";
    std::cout << "\n";


    std::cout << "\nBeffore clipping:\n" << align;
    setClippedBeginPosition(row1, 1);
    setClippedEndPosition(row1, 7);
    setClippedBeginPosition(row2, 1);
    setClippedEndPosition(row2, 7);
    std::cout << "\nAfter clipping:\n" << align;

    std::cout << std::endl << "ViewToSource1: ";
    for(unsigned i = 0; i < length(row1); ++i)
        std::cout << toSourcePosition(row1, i) << ",";

    std::cout << std::endl << "ViewToSource2: ";
    for(unsigned i = 0; i < length(row2); ++i)
        std::cout << toSourcePosition(row2, i) << ",";
    std::cout << std::endl;

    std::cout << std::endl << "SourceToView1: ";
    for(unsigned i = 0; i < length(source(row1)); ++i)
        std::cout << toViewPosition(row1, i) << ",";

    std::cout << std::endl << "SourceToView2: ";
    for(unsigned i = 0; i < length(source(row2)); ++i)
        std::cout << toViewPosition(row2, i) << ",";
    std::cout << std::endl;

    
    typedef Iterator<TRow>::Type TRowIterator;
    //clearClipping(row1);
    TRowIterator it    = begin(row1);
    TRowIterator itEnd = end(row1);
    for(; it != itEnd; ++it) {

        if(isGap(it))
            std::cout << gapValue<char>();
        else
            std::cout << *it;
    }
    std::cout << std::endl;

    return;
}

int main() {

    basic();    
    return 0;
}
