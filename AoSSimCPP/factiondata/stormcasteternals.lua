--Abilities declared globally as most are used multiple times
-- These are all incomplete and unimplemented as the mechanisms need to be added to the cpp side
SigmariteShields = 
{
    name = "Sigmarite Shields",
    type = "",
    effect = 
        function ()
        end 
}

faction = 
{
    name = "Stormcast Eternals",
    models = 
    {
        --[[{
            name = "Sample Model",
            stats = 
            {
                move = 4,
                save = 4,
                bravery = 8,
                wounds = 2
            },
            matchedData =
            {
                unitSize = 5,
                unitCost = 100
            },
            keywords = 
            {
                "ORDER",
                "SOMETHING", 
                "LOOKAKEYWORD"
            },
            meleeWeapons = 
            {
                {
                    name = "Sword",
                    range = 1,
                    attacks = 1,
                    toHit = 3,
                    toWound = 4,
                    rend = -1,
                    damage = 2
                }
            }
        },--]]

        {
            name = "Liberators (Warhammer and Shield)",
            stats = 
            {
                move = 5,
                save = 4,
                bravery = 6,
                wounds = 2
            },
            matchedData =
            {
                unitSize = 5,
                unitCost = 100
            },
            keywords = 
            {
                "ORDER",
                "CELESTIAL", 
                "HUMAN",
                "STORMCAST ETERNAL",
                "REDEEMER",
                "LIBERATORS"
            },
            meleeWeapons = 
            {
                {
                    name = "Warhammer",
                    range = 1,
                    attacks = 2,
                    toHit = 4,
                    toWound = 3,
                    rend = 0,
                    damage = 1
                }
            },
            abilities = 
            {
                SigmariteShields,
            }
        }
    }
}

