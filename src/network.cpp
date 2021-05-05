/*  Graph A (from document)
    Nodes: {A, B}
    Rules: {A = !B}, {B = A}
    Truth Table:{{0, 0}, {1, 0},
                 {0, 1}, {0, 0},
                 {1, 0}, {1, 1},
                 {1, 1}, {0, 1}}

                   {B, A}
    A Truth Table: {0, 1,
                    1, 0}

                   {A, B}
    B Truth Table: {0, 0,
                    1, 1}

    Network Truth Table: {{0, 1, 1, 0}, 
                          {0, 0, 1, 1}}
*/

std::vector<std::vector<int>> ATT = {{0, 0}, {1, 0},
                                     {0, 1}, {0, 0},
                                     {1, 0}, {1, 1},
                                     {1, 1}, {0, 1}};

int ATT2[8][2] = {{0, 0}, {1, 0},
                  {0, 1}, {0, 0},
                  {1, 0}, {1, 1},
                  {1, 1}, {0, 1}};

/*  Graph B (from document)
    Nodes: {A, B, C}
    Rules: {A = C & !B}, {B = C}, {C = A}

    Truth Table:{{0, 0, 0}, {0, 0, 0},
                 {0, 0, 1}, {1, 1, 0},
                 {0, 1, 0}, {0, 0, 0},
                 {0, 1, 1}, {0, 1, 0},
                 {1, 0, 0}, {0, 0, 1},
                 {1, 0, 1}, {1, 1, 1},
                 {1, 1, 0}, {0, 0, 1},
                 {1, 1, 1}, {0, 1, 1}}

                   {B, C, A}
    A Truth Table: {0, 0, 0,
                    0, 1, 1,
                    1, 0, 0,
                    1, 1, 0}

                   {B, C}
    C Truth Table: {0, 0,
                    1, 1}
                    
                   {A, C}
    C Truth Table: {0, 0,
                    1, 1}

    Network Truth Table: {{0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0}, 
                          {0, 0, 1, 1},
                          {0, 0, 1, 1}}
*/

std::vector<std::vector<int>> BTT = {{0, 0, 0}, {0, 0, 0},
                                     {0, 0, 1}, {1, 1, 0},
                                     {0, 1, 0}, {0, 0, 0},
                                     {0, 1, 1}, {0, 1, 0},
                                     {1, 0, 0}, {0, 0, 1},
                                     {1, 0, 1}, {1, 1, 1},
                                     {1, 1, 0}, {0, 0, 1},
                                     {1, 1, 1}, {0, 1, 1}};