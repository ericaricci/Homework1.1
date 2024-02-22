#include <iostream>
#include <vector>
//Erica Ricci AERSP424
//sourced from chat GPT
int main() {
    // Airplane design limits
    const double maxGrossWeight = 2950.0;
    const double forwardCGLimit = 82.1;
    const double aftCGLimit = 84.7;

    // User inputs
    double emptyWeight, emptyWeightMoment;
    int numFrontSeatOccupants, numRearSeatOccupants;
    std::vector<double> frontSeatWeights, rearSeatWeights;
    double frontSeatMomentArm, rearSeatMomentArm;
    int usableFuelGallons;
    double fuelWeightPerGallon, fuelTankMomentArm;
    double baggageWeight, baggageMomentArm;

    // Get user inputs
    std::cout << "Enter Airplane empty weight (pounds): ";
    std::cin >> emptyWeight;
    std::cout << "Enter Airplane empty-weight moment (pounds-inches): ";
    std::cin >> emptyWeightMoment;

    // Get inputs for front seat occupants
    std::cout << "Enter the number of front seat occupants: ";
    std::cin >> numFrontSeatOccupants;
    frontSeatWeights.resize(numFrontSeatOccupants);
    std::cout << "Enter the weight of each front seat occupant (pounds): ";
    for (int i = 0; i < numFrontSeatOccupants; ++i) {
        std::cin >> frontSeatWeights[i];
    }
    std::cout << "Enter the Front seat moment arm (inches): ";
    std::cin >> frontSeatMomentArm;

    // Get inputs for rear seat occupants
    std::cout << "Enter the number of rear seat occupants: ";
    std::cin >> numRearSeatOccupants;
    rearSeatWeights.resize(numRearSeatOccupants);
    std::cout << "Enter the weight of each rear seat occupant (pounds): ";
    for (int i = 0; i < numRearSeatOccupants; ++i) {
        std::cin >> rearSeatWeights[i];
    }
    std::cout << "Enter the Rear seat moment arm (inches): ";
    std::cin >> rearSeatMomentArm;

    // Get inputs for usable fuel
    std::cout << "Enter the number of gallons of usable fuel: ";
    std::cin >> usableFuelGallons;
    std::cout << "Enter the Usable fuel weight per gallon (pounds): ";
    std::cin >> fuelWeightPerGallon;
    std::cout << "Enter the Fuel tank moment arm (inches): ";
    std::cin >> fuelTankMomentArm;

    // Get inputs for baggage
    std::cout << "Enter the Baggage weight (pounds): ";
    std::cin >> baggageWeight;
    std::cout << "Enter the Baggage moment arm (inches): ";
    std::cin >> baggageMomentArm;

    // Calculate gross weight and C.G. location
    double totalFrontSeatWeight = 0.0;
    for (double weight : frontSeatWeights) {
        totalFrontSeatWeight += weight;
    }

    double totalFrontSeatMoment = numFrontSeatOccupants * totalFrontSeatWeight * frontSeatMomentArm;

    double totalRearSeatWeight = 0.0;
    for (double weight : rearSeatWeights) {
        totalRearSeatWeight += weight;
    }

    double totalRearSeatMoment = numRearSeatOccupants * totalRearSeatWeight * rearSeatMomentArm;

    double fuelWeight = usableFuelGallons * fuelWeightPerGallon;
    double fuelMoment = fuelWeight * fuelTankMomentArm;

    double grossWeight = emptyWeight + totalFrontSeatWeight + totalRearSeatWeight + fuelWeight + baggageWeight;
    double totalMoment = emptyWeightMoment + totalFrontSeatMoment + totalRearSeatMoment + fuelMoment + baggageWeight * baggageMomentArm;

    double cgLocation = totalMoment / grossWeight;

    // Check if within design limits
    if (grossWeight <= maxGrossWeight && cgLocation >= forwardCGLimit && cgLocation <= aftCGLimit) {
        std::cout << "The airplane is within design limits. Gross Weight: " << grossWeight << " C.G. Location: " << cgLocation << std::endl;
    }
    else {
        // Calculate the required fuel adjustment to meet the limits
        double requiredFuelAdjustment = 0.0;
        if (grossWeight > maxGrossWeight) {
            requiredFuelAdjustment = (grossWeight - maxGrossWeight) / fuelWeightPerGallon;
        }
        else if (cgLocation < forwardCGLimit) {
            requiredFuelAdjustment = (forwardCGLimit - cgLocation) * grossWeight / fuelTankMomentArm;
        }
        else if (cgLocation > aftCGLimit) {
            requiredFuelAdjustment = (cgLocation - aftCGLimit) * grossWeight / fuelTankMomentArm;
        }

        // Adjust the fuel weight accordingly
        usableFuelGallons -= requiredFuelAdjustment;

        // Recalculate the gross weight and C.G. location
        fuelWeight = usableFuelGallons * fuelWeightPerGallon;
        fuelMoment = fuelWeight * fuelTankMomentArm;

        grossWeight = emptyWeight + totalFrontSeatWeight + totalRearSeatWeight + fuelWeight + baggageWeight;
        totalMoment = emptyWeightMoment + totalFrontSeatMoment + totalRearSeatMoment + fuelMoment + baggageWeight * baggageMomentArm;

        cgLocation = totalMoment / grossWeight;

        std::cout << "Adjusted Gross Weight: " << grossWeight << " Adjusted C.G. Location: " << cgLocation << std::endl;
    }

    return 0;
}
