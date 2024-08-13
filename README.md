# CirFinCREATE - ECOMENU 🌱🍳
Our project ECOMENU is a recipe recommendation platform that empowers users to make environmentally conscious food choices. The app focuses on sustainability by recommending recipes based on the carbon footprint of their ingredients. By leveraging a database of 350 food ingredients and 2000 recipes, the app provides users with options that minimize environmental impact. We aim to make sustainability a part of everyday cooking, contributing to a more climate-conscious world.

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
