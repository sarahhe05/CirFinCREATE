# CirFinCREATE - BoostHacksII - ECOMENU 🌱🍳
Balancing life's demands while considering the best choices for the planet can be challenging. As students, parents, and working adults, our decisions are often driven by our immediate needs, such as income and the care of loved ones. However, we believe that caring for our planet shouldn't be a compromise but rather a convenient task integrated into our daily lives. That's why we've created Ecomenu—a platform designed to empower families to make sustainable, environmentally-conscious meals with ease.

To bring this idea to life, we gathered data on popular and sustainable recipes, along with their associated carbon emissions. After thoroughly cleaning the data to ensure consistency and accuracy, we developed an efficient program that displays recipes based on user input. Through this process, we learned how to effectively sort and extract information in various formats. Additionally, as we tested our programs, it became evident just how significantly the carbon emissions of each meal can impact our environment over time.

One of the challenges we faced was finding and learning about a suitable hosting engine for our website. Furthermore, due to the varying formats within the database, we had to devise creative solutions to accurately extract values such as units, amounts, and ingredients in order to calculate the carbon footprint of each recipe.

Check out our DevPost submissions!
- [CirFin CREATE Civic Achievement Award](https://devpost.com/software/ecomenu)
- [Boost Hacks II Most Creative Hacks](https://devpost.com/software/ecomenu-c6rb2l)

## Getting Started

### Prerequisites
- Node.js
- npm
- g++

### Installation
1. Clone the repository:
<pre> <code> git clone https://github.com/sarahhe05/CirFinCREATE-BoostHacksII-ECOMENU </code> </pre>

2. Install dependencies:
<pre> <code> npm install </code> </pre>

3. Compile
<pre> <code> g++ -o filterDisplay filterDisplay.cpp recipe.cpp </code> </pre>

4. Start the server:
<pre> <code> node server.js </code> </pre>

Open http://localhost:8080 with your browser to see the result.

## Data
We compiled carbon footprint and environmental data from multiple data sources for a comprehensive collection. 

### Ingredients
- [AGRIBALYSE Data Access](https://doc.agribalyse.fr/documentation-en/agribalyse-data/data-access)
- [SU-EATABLE LIFE Dataset](https://figshare.com/articles/dataset/SU-EATABLE_LIFE_a_comprehensive_database_of_carbon_and_water_footprints_of_food_commodities/13271111?file=27921765)
- [Environment Impact of Food Production](https://www.kaggle.com/datasets/selfvivek/environment-impact-of-food-production)

#### Columns:
- `Ingredient`: The name of the ingredient.
- `Carbon Footprint`: The carbon dioxide emission levels for each ingredient, measured in CO2e per kilogram of food.

### Recipes
- [Recipe Dataset](https://www.kaggle.com/datasets/wilmerarltstrmberg/recipe-dataset-over-2m)

#### Columns:
- `Title`: The name of the dish.
- `Ingredients`: The names and amounts of ingredients used to make the dish.
- `Directions`: Instructions on how to cook the dish.
- `NER`: A list of ingredients used, without amounts or units.
- `Valid Ingredient Count`: The number of ingredients used in the dish.
- `Carbon`: The estimated total carbon emissions from the dish.

### Global Temperature
- [NASA Global Temperature Data](https://climate.nasa.gov/vital-signs/global-temperature/?intent=121)
