dofile("../AbilityTypes")

-- Abilities declared globally as most are used multiple times
-- These are all incomplete and unimplemented as the mechanisms need to be added to the cpp side
StardrakeIcon = {}
Wardrum = {}
StardrakeShield =
{   
    name = "Stardrake Shield",
    phase = SaveRoll,
    effect = 
        function (SaveAction)
            if (AttackAction.WeaponProfile.Rend > -2) then AttackAction.WeaponProfile.Rend = 0 end
            return AttackAction
        end 
}
StarBuckler = StardrakeShield

OrderedCohort =
{
    name = "OrderedCohort",
    phase = "",
    effect =
        function()
        end 
}
EnergyTransference = {}

SwornGuardians =
{
    name = "Sworn Guardians",
    type = "",
    effect = 
        function ()
        end
}

faction = 
{
    name = "Seraphon",
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
                blockSize = 5,
                blockCost = 100
                maxBlocks = 4
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
            },--]]
        
        {
            name = "Saurus Warriors (Clubs)",
            stats = 
            {
                move = 5,
                save = 5,
                bravery = 10,
                wounds = 1
            },
            matchedData =
            {
                blockSize = 10,
                blockCost = 90,
                maxBlocks = 4
            },
            keywords = 
            {
                "ORDER",
                "DAEMON", 
                "CELESTIAL", 
                "SERAPHON", 
                "SAURUS", 
                "SAURUS WARRIORS"
            },
            meleeWeapons = 
            {
                {
                    name = "Celestite Club",
                    range = 1,
                    attacks = 1,
                    toHit = 4,
                    toWound = 3,
                    rend = 0,
                    damage = 1
                } ,
                {
                    name = "Powerful Jaws and Stardrake Shield",
                    range = 1,
                    attacks = 1,
                    toHit = 5,
                    toWound = 4,
                    rend = 0,
                    damage = 1
                }
            },
        
            abilities =
            {
                StardrakeIcon,
                Wardrum,
                StardrakeShield,
                OrderedCohort
            }
        },

        {
            name = "Saurus Warriors (Spears)",
            stats = 
            {
                move = 5,
                save = 5,
                bravery = 10,
                wounds = 1
            },
            matchedData =
            {
                blockSize = 10,
                blockCost = 90,
                maxBlocks = 4
            },
            keywords = 
            {
                "ORDER",
                "DAEMON", 
                "CELESTIAL", 
                "SERAPHON", 
                "SAURUS", 
                "SAURUS WARRIORS"
            },
            meleeWeapons = 
            {
                {
                    name = "Celestite Spear",
                    range = 2,
                    attacks = 1,
                    toHit = 4,
                    toWound = 4,
                    rend = 0,
                    damage = 1
                } ,
                {
                    name = "Powerful Jaws and Stardrake Shield",
                    range = 1,
                    attacks = 1,
                    toHit = 5,
                    toWound = 4,
                    rend = 0,
                    damage = 1
                }
            },
        
            abilities =
            {
                StardrakeIcon,
                Wardrum,
                StardrakeShield,
                OrderedCohort
            }
        },

        {
            name = "Saurus Guard",
            stats = 
            {
                move = 5,
                save = 4,
                bravery = 10,
                wounds = 1
            },
            matchedData =
            {
                blockSize = 5,
                blockCost = 100,
                maxBlocks = 4
            },
            keywords = 
            {
                "ORDER",
                "DAEMON", 
                "CELESTIAL", 
                "SERAPHON", 
                "SAURUS", 
                "SAURUS GUARD"
            },
            meleeWeapons = 
            {
                {
                    name = "Celestite Polearm",
                    range = 1,
                    attacks = 2,
                    toHit = 3,
                    toWound = 3,
                    rend = -1,
                    damage = 1
                } ,
                {
                    name = "Powerful Jaws and Stardrake Shield",
                    range = 1,
                    attacks = 1,
                    toHit = 5,
                    toWound = 4,
                    rend = 0,
                    damage = 1
                }
            },
        
            abilities =
            {
                StardrakeIcon,
                Wardrum,
                StardrakeShield,
                SwornGuardians
            }
        },

        {
            name = "Skinks (Javelins and Shields)",
            stats = 
            {
                move = 8,
                save = 6,
                bravery = 10,
                wounds = 1
            },

            matchedData =
            {
                blockSize = 10,
                blockCost = 80,
                maxBlocks = 4
            },
            keywords = 
            {
                "ORDER",
                "DAEMON", 
                "CELESTIAL", 
                "SERAPHON", 
                "SKINKS"
            },
            meleeWeapons = 
            {
                {
                    name = "Meteoric Javelin",
                    range = 1,
                    attacks = 1,
                    toHit = 6,
                    toWound = 5,
                    rend = -1,
                    damage = 1
                }
            },
            rangedWeapons = 
            {
                {
                    name = "Meteoric Javelin",
                    range = 8,
                    attacks = 1,
                    toHit = 5,
                    toWound = 4,
                    rend = 0,
                    damage = 1
                }
            },
            abilities =
            {
                CelestialCohort,
                StarBuckler
            }
        },
        {
            name = "Kroxigor",
            stats = 
            {
                move = 8,
                save = 4,
                bravery = 10,
                wounds = 4
            },
            matchedData =
            {
                blockSize = 3,
                blockCost = 180,
                maxBlocks = 4
            },
            keywords = 
            {
                "ORDER",
                "DAEMON", 
                "CELESTIAL", 
                "SERAPHON", 
                "KROXIGOR", 
            },
            meleeWeapons = 
            {
                {
                    name = "Drakebite Maul",
                    range = 2,
                    attacks = 4,
                    toHit = 4,
                    toWound = 3,
                    rend = 0,
                    damage = 2
                } ,
                {
                    name = "Vice-like Jaws",
                    range = 1,
                    attacks = 1,
                    toHit = 4,
                    toWound = 3,
                    rend = -1,
                    damage = 1
                }
            },
            abilities =
            {
                EnergyTransference
            }
        },
    }
}

