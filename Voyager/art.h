#pragma once

#include <string>

class Art {
private:
    std::string art;

public:
    std::string getArt() const;
    void setArtToShip();
    void setArtToOcean();
    void setArtToDesert();
    void setArtToIce();
    void setArtToForest();
    void setArtToVolcano();
    void setArtToGasGiant();
    void setArtToCity();
    void setArtToWasteLand();
    void setArtToTitle();
    void setArtToAguila();
};