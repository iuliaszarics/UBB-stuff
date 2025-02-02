#include "htmldataloader.h"

void HTMLDataLoader::Save(vector<TrenchCoat> vector) {

    std::string tab = "    ";

    ofstream file("data.html");


    file << "<!DOCTYPE html>\n";
    file << "<html>\n";
    file << "<head>\n";
    file << tab << "<title>Trench Coats</title>\n";
    file << "</head>\n";
    file << "<body>\n";
    file << tab << "<table border=\"1\">\n";
    file << tab << tab << "<tr>\n";
    file << tab << tab << tab << "<td>Size</td>\n";
    file << tab << tab << tab << "<td>Price</td>\n";
    file << tab << tab << tab << "<td>Quantity</td>\n";
    file << tab << tab << tab << "<td>Colour</td>\n";
    file << tab << tab << tab << "<td>Photo</td>\n";
    file << tab << tab << "</tr>\n";

    for (auto& i : vector) {
        file << tab << tab << "<tr>\n";
        file << tab << tab << tab << "<td>" << i.getTrenchSize() << "</td>\n";
        file << tab << tab << tab << "<td>" << i.getTrenchPrice() << "</td>\n";
        file << tab << tab << tab << "<td>" << i.getTrenchQuantity() << "</td>\n";
        file << tab << tab << tab << "<td>" << i.getTrenchColour() << "</td>\n";
        file << tab << tab << tab << "<td><a href=\"" << i.getTrenchPhotographyLink() << "\">Photo</a></td>\n";
        file << tab << tab << "</tr>\n";
    }

    file << tab << "</table>\n";
    file << "</body>\n";
    file << "</html>\n";

    file.close();

}

void HTMLDataLoader::Open() {
    system("start data.html");
}
