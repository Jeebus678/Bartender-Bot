typedef struct
{
  char liquor[24];
  unsigned int portion;
} Ingridient;

typedef struct
{
  char name[30];
  Ingridient ingridients[8];
} Cocktail;

Cocktail cocktails[] = {
    {"Americano", {{"campari", 0}, {"red vermouth", 0}, {"soda", 0}}},
    {"Aviation", {{"gin", 0}, {"cherry liqueur", 0}, {"creme de violette", 0}, {"lemon juice", 0}}},
    {"B52 Cocktail", {{"kahlua", 0}, {"baileys", 0}, {"trand marnier", 0}}},
    {"Barracuda", {{"amber rum", 0}, {"galliano", 0}, {"sparkling wine", 0}, {"lime juice", 0}, {"pineapple juice", 0}}},
    {"Bellini", {{"prosecco", 0}, {"peach juice", 0}}},
    {"Between The Sheets", {{"white rum", 0}, {"cognac", 0}, {"cointreau", 0}, {"lemon juice", 0}}},
    {"Black Russian", {{"kahlua", 0}, {"vodka", 0}}},
    {"Bloody Mary", {{"vodka", 0}, {"tomato juice", 0}, {"tabasco Sauce", 0}, {"worcestershire sauce", 0}}},
    {"Brandy Alexander", {{"cognac", 0}, {"white creme de cacao", 0}, {"cream (milk)", 0}}},
    {"Caipirinha", {{"cachaca", 0}, {"lime juice", 0}, {"sugar", 0}}},
    {"Caipiroska", {{"vodka", 0}, {"lime juice", 0}, {"sugar", 0}}},
    {"Cosmopolitan", {{"vodka", 0}, {"cointreau", 0}, {"cranberry juice", 0}, {"lime juice", 0}}},
    {"Cuba Libre", {{"white rum", 0}, {"cola", 0}, {"lime juice", 0}}},
    {"Daiquiri", {{"white rum", 0}, {"lime juice", 0}, {"simple syrup", 0}}},
    {"Dirty Martini", {{"vodka", 0}, {"white vermouth", 0}, {"olive brine", 0}}},
    {"Dry Martini", {{"gin", 0}, {"white vermouth", 0}}},
    {"Dubonnet Cocktail", {{"dubonnet", 0}, {"gin", 0}}},
    {"Espresso Martini", {{"vodka", 0}, {"kahlua", 0}, {"espresso", 0}, {"simple syrup", 0}}},
    {"French 75", {{"gin", 0}, {"prosecco", 0}, {"lemon juice", 0}, {"soda", 0}, {"simple syrup", 0}}},
    {"French Martini", {{"vodka", 0}, {"raspberry liqueur", 0}, {"pineapple juice", 0}}},
    {"Fuzzy Navel", {{"vodka", 0}, {"peach schnapps", 0}, {"orange juice", 0}}},
    {"Gimlet", {{"gin", 0}, {"lime juice", 0}, {"simple syrup", 0}}},
    {"Gin Fizz ", {{"gin", 0}, {"lemon juice", 0}, {"soda", 0}, {"simple syrup", 0}}},
    {"Harvey Wallbanger", {{"vodka", 0}, {"galliano", 0}, {"orange juice", 0}}},
    {"Hurricane", {{"dark rum", 0}, {"white rum", 0}, {"lime juice", 0}, {"passionfruit syrup", 0}, {"grenadine", 0}}},
    {"Irish Coffee", {{"irish whiskey", 0}, {"black coffee", 0}, {"brown sugar", 0}, {"whipping cream", 0}}},
    {"Lemon Drop Martini", {{"vodka", 0}, {"cointreau", 0}, {"lemon juice", 0}}},
    {"Long Island Iced Tea", {{"gin", 0}, {"tequila", 0}, {"white rum", 0}, {"vodka", 0}, {"cointreau", 0}, {"lemon juice", 0}, {"cola", 0}, {"simple syrup", 0}}},
    {"Mai Tai", {{"dark rum", 0}, {"curacao", 0}, {"lemon juice", 0}, {"grenadine", 0}, {"orgeat syrup", 0}}},
    {"Manhattan", {{"rye whisky", 0}, {"red vermouth", 0}, {"angostura bitters", 0}}},
    {"Margarita", {{"tequila", 0}, {"cointreau", 0}, {"lime juice", 0}}},
    {"Martini (Classic)", {{"gin", 0}, {"white vermouth", 0}}},
    {"Mint Julep", {{"bourbon", 0}, {"mint", 0}, {"water", 0}, {"sugar", 0}}},
    {"Mojito ", {{"white rum", 0}, {"lime juice", 0}, {"mint", 0}, {"water", 0}, {"sugar", 0}}},
    {"Moscow Mule", {{"vodka", 0}, {"ginger beer", 0}, {"lime juice", 0}}},
    {"Mudslide", {{"vodka", 0}, {"kahlua", 0}, {"baileys", 0}, {"cream (milk)", 0}, {"whipping cream", 0}}},
    {"Negroni", {{"gin", 0}, {"campari", 0}, {"red vermouth", 0}}},
    {"Old Fashioned", {{"bourbon", 0}, {"angostura bitters", 0}, {"simple syrup", 0}}},
    {"Pimm’s Cup", {{"pimm’s #1", 0}, {"ginger ale", 0}, {"soda", 0}}},
    {"Pina Colada", {{"white rum", 0}, {"pineapple juice", 0}, {"coconut cream (milk)", 0}}},
    {"Pink Lady", {{"gin", 0}, {"grenadine", 0}, {"cream (milk)", 0}}},
    {"Pink Martini", {{"vodka", 0}, {"white vermouth", 0}, {"grenadine", 0}, {"orange bitters", 0}}},
    {"Pisco Sour", {{"pisco", 0}, {"lime juice", 0}, {"egg white", 0}, {"simple syrup", 0}, {"angostura bitters", 0}}},
    {"Rob Roy ", {{"scotch", 0}, {"sweet vermouth", 0}, {"angostura bitters", 0}}},
    {"Rusty Nail", {{"scotch", 0}, {"drambuie", 0}}},
    {"Sex On The Beach", {{"vodka", 0}, {"peach schnapps", 0}, {"cranberry juice", 0}, {"orange juice", 0}}},
    {"Sidecar", {{"cognac", 0}, {"cointreau", 0}, {"lemon juice", 0}}},
    {"Singapore Sling (Original)", {{"gin", 0}, {"cointreau", 0}, {"benedictine", 0}, {"cherry Heering", 0}, {"pineapple juice", 0}, {"lime juice", 0}, {"grenadine", 0}, {"angostura bitters", 0}}},
    {"Singapore Sling (Simple)", {{"gin", 0}, {"cherry brandy", 0}, {"lemon juice", 0}, {"grenadine", 0}, {"soda", 0}, {"simple syrup", 0}}},
    {"Tequila Sunrise", {{"cointreau", 0}, {"orange juice", 0}, {"grenadine", 0}}},
    {"Tom Collins", {{"gin", 0}, {"lemon juice", 0}, {"simple syrup", 0}, {"soda", 0}}},
    {"Vesper", {{"gin", 0}, {"vodka", 0}, {"lillet blanc", 0}}},
    {"Whiskey Sour", {{"bourbon", 0}, {"lemon juice", 0}, {"simple syrup", 0}}},
    {"White Russian", {{"kahlua", 0}, {"vodka", 0}, {"cream (milk)", 0}}},
    {"Woo Woo", {{"vodka", 0}, {"peach schnapps", 0}, {"cranberry juice", 0}}},
    {"Zombie", {{"overproof rum", 0}, {"dark rum", 0}, {"white rum", 0}, {"curacao", 0}, {"orange juice", 0}, {"lemon juice", 0}, {"grenadine", 0}, {"angostura bitters", 0}}}};


