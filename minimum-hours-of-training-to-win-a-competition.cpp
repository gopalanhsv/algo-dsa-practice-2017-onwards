class Solution {
public:
    int
    minNumberOfHours(int initialEnergy, int initialExperience,
                     vector<int>& energy, vector<int>& experience) {
        
        int nOpponents = energy.size();
        // Tracks the excess energy and experience required
        // to beat each opponent
        int excessExperienceReqd = 0;
        int exessEnergyReqd = 0;
        // Tracks the state of experience and energy prior to/post
        // facing an opponent
        auto currExperience = initialExperience;
        auto currEnergy = initialEnergy;
        // Fight the opponents one by one
        for (int i = 0; i != nOpponents; ++i) {
            // Determine the experience and energy required to
            // beat the current opponent
            auto energyReqd = energy[i] + 1;
            auto experienceReqd = experience[i] + 1;
            
            if (currExperience < experienceReqd) {
                // Current experience is insufficient to beat
                // opponent. Compute minimum extra experience reqd to
                // beat opponent and add it self experience
                auto extraExperienceReqd = experienceReqd - currExperience;
                currExperience += extraExperienceReqd;
                excessExperienceReqd += extraExperienceReqd;
            }
            if (currEnergy < energyReqd) {
                // Current energy is insufficient to beat
                // opponent. Compute minimum extra energy reqd to
                // beat opponent and add it self energy
                auto extraEnergyReqd = energyReqd - currEnergy;
                currEnergy += extraEnergyReqd;
                exessEnergyReqd += extraEnergyReqd;
            }
            
            // Adjust energy and experience post beating the opponent
            currEnergy -= energy[i];
            currExperience += experience[i];
        }
        
        // Min training hours reqd would the sum of the
        // excess energy and experience required
        return excessExperienceReqd + exessEnergyReqd;
    }
};
