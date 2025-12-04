#include "help.h"
#include <string>

using namespace std;

string Help::getGeneralHelp() const {
    string text = getScanHelp() + "\n\n" + getTravelHelp() + "\n\n" +
                  getExchangeHelp() + "\n\n" + getStoreHelp();
    return text;
}

string Help::getScanHelp() const {
    string text =
        "scan - a general purpose tool for scanning the surrounding area\n\n"
        "Usage:\n"
        "\tscan [options]\n"
        "Options:\n"
        "\t-p | --planets\tscan your surroundings for nearby planets\n"
        "\t-a | --area\tscan your general area for targets to interact with";
    return text;
}

string Help::getTravelHelp() const {
    string text =
        "travel - a navigation tool for traversing the galaxy\n\n"
        "Usage:\n"
        "\tscan [options] <args>\n"
        "Options:\n"
        "\t[-d | --destination] <index>\ttravel to a planet of the given index\n"
        "\t[-p | --position] <x_pos> <y_pos> <z_pos>\tmove to a given (x,y,z) coordinate";
    return text;
}

string Help::getExchangeHelp() const {
    string text = "exchange - trade in points and samples for resources\n\n"
                  "Usage:\n"
                  "\texchange [options] <args>\n"
                  "Options:\n"
                  "\t[sample] <index>\ttrade in a sample in storage of the "
                  "given index\n"
                  "\t[fuel] <points>\texchange your points to refuel the ship\n"
                  "\t[health] <points>\t exhcange your points to heal";
    return text;
}
string Help::getStoreHelp() const {
    string text = "store - move items from your inventory to storage\n\n"
                  "Usage:\n"
                  "\tstore <index>";
    return text;
}
