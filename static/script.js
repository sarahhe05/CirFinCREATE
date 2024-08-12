$(document).ready(function() {
    const availableIngredients = [
        "albacore",
        "alfalfa",
        "alfonsino",
        "almond",
        "almond covered with chocolate",
        "almond milk",
        "almond paste",
        "anchovy",
        "anglerfish",
        "apple",
        "apple juice",
        "apricot",
        "artichoke",
        "asiago",
        "asparagus",
        "atlantic herring",
        "atlantic mackerel",
        "avocado",
        "azuki bean flour",
        "bacon",
        "banana",
        "barley",
        "barnacle",
        "bean",
        "beef",
        "beer",
        "beet sugar",
        "beetroot",
        "black pepper",
        "blackberry",
        "blueberry",
        "blueberry juice",
        "bluefin tuna",
        "brassicas",
        "bread",
        "broccoli",
        "broiler",
        "brown crab",
        "buckwheat flour",
        "buffalo milk",
        "butter",
        "cabagge",
        "cakes and croissant",
        "camembert",
        "cane sugar",
        "canned beans",
        "canned carrots",
        "canned corn",
        "canned green beans",
        "canned tuna",
        "carp",
        "carrot",
        "carrots",
        "cashew nut",
        "cassava",
        "catfish",
        "cauliflower",
        "celery",
        "cheddar",
        "cheese",
        "cherry",
        "chestnut",
        "chicken",
        "chickpea",
        "chicory root",
        "chicory witloof",
        "chilly",
        "chocolate",
        "citrus fruit",
        "clementine",
        "cocoa cakes and croissant",
        "coconut",
        "coconut milk",
        "cod",
        "cod stick",
        "coffee",
        "coffee bean",
        "coffee parchment",
        "common sole",
        "cookie",
        "cornflakes",
        "cow milk",
        "cowpea",
        "crackers",
        "cranberry",
        "cranberry juice",
        "cream",
        "crispbread",
        "cucumber",
        "currant",
        "cuttlefish",
        "dark chocolate",
        "date",
        "diamond fish",
        "duck",
        "durum wheat",
        "eel",
        "egg",
        "eggplant",
        "emmental",
        "emu",
        "european anchovy",
        "european pilchard",
        "ewe",
        "exotic fruit",
        "extruded flaxseed",
        "fennel",
        "fig",
        "fig juice",
        "fish",
        "fish mixed",
        "fish stick",
        "flatfish",
        "flathead",
        "flavored cracker",
        "flaxseed",
        "fork beard",
        "french bean",
        "gadidae",
        "garlic",
        "gerkin",
        "ginger",
        "goat cheese",
        "goat milk",
        "gooseberry",
        "graham flour",
        "grain maize",
        "grana padano",
        "grape",
        "grapefruit",
        "great scallop",
        "green bean",
        "ground coffee",
        "groundnut",
        "guava",
        "haddock",
        "hake",
        "hazelnut",
        "hazelnut covered with chocolate",
        "hazelnut cream",
        "hazelnut paste",
        "hemp",
        "herring",
        "honey",
        "ice cream",
        "jasmine rice",
        "kangaroo meat",
        "ketchup",
        "kid goat",
        "kiwi",
        "kiwi juice",
        "krill",
        "lamb",
        "leek",
        "lemon",
        "lentil",
        "lettuce",
        "lime",
        "ling",
        "lobster",
        "lupin",
        "mackerel",
        "maize",
        "maize flour",
        "maize grain",
        "makerel fish stick",
        "mandarin",
        "mango",
        "mango juice",
        "margarine",
        "mascarpone",
        "mayonnaise",
        "mealworm",
        "megrim",
        "melon",
        "milk",
        "milk chocolate",
        "millet",
        "millet flour",
        "mineral water",
        "mixed fish",
        "mixed nuts",
        "mozzarella",
        "mung bean flour",
        "mushroom",
        "mussel",
        "neck",
        "nuts",
        "oat",
        "oat grain",
        "oatmeal",
        "octopus",
        "olive",
        "olive oil",
        "onion",
        "orange",
        "orange juice",
        "other fruit",
        "other pulses",
        "other vegetables",
        "palm fruit bunch",
        "palm nut",
        "palm oil",
        "parmigiano reggiano",
        "pasta",
        "pea",
        "peach",
        "peanut",
        "peanut butter",
        "peanut oil",
        "peanut paste",
        "pear",
        "pear juice",
        "peas",
        "pecorino",
        "pepper",
        "pesto",
        "pesto without garlic",
        "pilchard",
        "pineapple",
        "pineapple juice",
        "pistachio",
        "plaice",
        "plum",
        "pollock",
        "pollock stick",
        "pomegranate",
        "pomelo",
        "pomfret",
        "porbeagle",
        "pork",
        "pork ham",
        "pork sausage",
        "potato",
        "poultry meat",
        "pumpkin",
        "quinoa",
        "quorne",
        "rabbit",
        "radish",
        "raisin",
        "rapeseed",
        "rapeseed oil",
        "raspberry",
        "red wine",
        "rhombus",
        "rice",
        "rice milk",
        "ricotta",
        "rock fish",
        "rockmelon",
        "root vegetables",
        "rye",
        "saithe",
        "salmon",
        "salt",
        "sardine",
        "sea bass",
        "seaweed",
        "sesame seed",
        "shark",
        "sheep milk",
        "shrimp",
        "skipjack tuna",
        "small trout",
        "snail",
        "soft wheat grain",
        "sole",
        "sorghum",
        "sorghum flour",
        "soy burger",
        "soy cream",
        "soy meal",
        "soy milk",
        "soy yogurt",
        "soybean",
        "soybean oil",
        "soymilk",
        "spinach",
        "spring faba bean",
        "spring pea",
        "squid",
        "starchy root",
        "stracchino",
        "strawberry",
        "strawberry juice",
        "suckler heifer",
        "sugar",
        "sunflower grain",
        "sunflower oil",
        "sunflower seed",
        "swardfish",
        "swede",
        "sweet potato",
        "tangerin",
        "tempe",
        "tofu",
        "tomato",
        "tomato & basil",
        "tomato arrabbiata",
        "tomatoes",
        "triticale grain",
        "trout",
        "tuna",
        "turbot",
        "turkey",
        "turnip",
        "vanilla",
        "veal",
        "vegetables",
        "vining pea",
        "walnut",
        "watermelon",
        "wheat",
        "wheat flour",
        "white wine",
        "whiting",
        "wholegrain crackers",
        "wine",
        "winter pea",
        "wool",
        "yeast",
        "yellowfin tuna",
        "yogurt",
        "zucchini"
    ];

    const selectedValues = [];

    $("#ingredientSearch").autocomplete({
        source: availableIngredients,
        minLength: 1,
        autoFocus: true,
        select: function(event, ui) {
            const value = ui.item.value;
            if (!selectedValues.includes(value)) {
                selectedValues.push(value);
                displaySelectedIngredients();
                // DisplayRecipes(value);
            }
            $(this).val(''); // Clear the input field after selection
            return false; // Prevent the selected value from being put into the input field
        }
    });

    function displaySelectedIngredients() {
        const container = $('#selectedIngredients');
        container.empty();
        selectedValues.forEach(function(value) {
            const tag = $(`<div class="tag">${value} <span>&times;</span></div>`);
            tag.find('span').click(function() {
                removeIngredient(value);
            });
            container.append(tag);
        });
    }

    function removeIngredient(value) {
        const index = selectedValues.indexOf(value);
        if (index !== -1) {
            selectedValues.splice(index, 1);
            displaySelectedIngredients();
        }
    }

    // // Handle form submission
    // $('#ingredientForm').submit(function(event) {
    //     event.preventDefault(); // Prevent the default form submission

    //     // Send the selected ingredients to the backend using AJAX
    //     $.ajax({
    //         url: '/submit', // Flask endpoint
    //         type: 'POST',
    //         contentType: 'application/json',
    //         data: JSON.stringify({ ingredients: selectedValues }),
    //         success: function(response) {
    //             console.log('Success:', response);
    //             // Optionally handle success, e.g., show a success message
    //         },
    //         error: function(error) {
    //             console.error('Error:', error);
    //             // Optionally handle error
    //         }
    //     });
    // });

    // function DisplayRecipes(value) {

    //     fetch('/search', {
    //         method: 'POST',
    //         headers: {
    //             'Content-Type': 'application/json'
    //         },
    //         body: JSON.stringify({ ingredient: value })
    //     })
    //     .then(response => response.json())
    //     .then(data => {
    //         document.getElementById('result').innerText = data.message;
    //     })
    //     .catch(error => console.error('Error:', error));
    // }

    // Submit form
    $('form').submit(function(event) {
        event.preventDefault();

        $.ajax({
            type: 'POST',
            url: '/submit',
            contentType: 'application/json',
            data: JSON.stringify({ selectedIngredients: selectedValues }),
            success: function(response) {
                displayResult(response.message);
            },
            error: function(xhr, status, error) {
                console.error('Error:', error);
            }
        });
    });

    // function displayResult(result) {
    //     // Assuming you want to display the result in the first accordion body
    //     $('#collapseOne .accordion-body').html(result);
    // }
    function displayResult(results) {
        // Clear existing accordion items
        $('#recipes-container').empty();
        
        // Loop through each result and create an accordion item
        results.forEach((item, index) => {
            const collapseId = `collapse${index+1}`;
            
            //Formats ingredients and directions as Lists
            const ingredientsList = item.ingredients.map(ingredient => `<li>${ingredient}</li>`).join('');
            const directionsList = item.directions.map(direction => `<li>${direction}</li>`).join('');
    
            const accordionItem = `
            </head>
                <link rel="stylesheet" href="/styles.css"/>  <!--Removed the static-->
                <div class="accordion-item">
                    <h2 class="accordion-header" id="heading${index + 1}">
                        <button class="accordion-button ${index === 0 ? '' : 'collapsed'}" 
                                type="button" data-bs-toggle="collapse" data-bs-target="#${collapseId}" 
                                aria-expanded="${index === 0}" aria-controls="${collapseId}">
                            <h2>${item.title}</h2>
                        </button>
                    </h2>
                    <div id="${collapseId}" class="accordion-collapse collapse ${index === 0 ? 'show' : ''}" data-bs-parent="#recipes-container">
                        <div class="accordion-body">
                            <h3>Ingredients</h3>
                            <ul>${ingredientsList}</ul>
                            <h3>Directions</h3>
                            <ul>${directionsList}</ul>
                            <h3>Carbon Footprint</h3>
                            <p>${item.carbonFootprint}</p>
                        </div>
                    </div>
                </div>
            `;
    
            $('#recipes-container').append(accordionItem);
        });
    }
});
