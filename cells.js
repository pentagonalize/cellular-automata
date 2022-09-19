world_width = 200;
world_height = 200;
cell_size = 5;
ruleset = [0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
// rulestring = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001010111110110011000111010101001000111111110111110101101110110110110001010111111111111111111111111111101011110010011011011110000101001101110110111101110000000111111011111001101101110011010110101111110000111110101101110001011111111110111111111110011111011101111111111110001011111010110001100111101111001111110001111101111110111111111110010101111111111001111011111111111"
ruleFrequency = [];
for (var i=0; i<512; i++){
    ruleFrequency.push(0);
}
interval = 1;

cellArray = new Array(world_width);
for (i = 0; i < world_width; i++) {
    cellArray[i] = new Array(world_height);
}
class Cell {
    constructor(x, y, state) {
        this.x = x;
        this.y = y;
        this.state = state;
        this.nextState = state;
    }
    update(cnn, cne, cee, cse, css, csw, cww, cnw, ruleset) {
        // sets the nextState
        var stateCode = 256 * cnn.state +
            128 * cne.state +
            64 * cee.state +
            32 * cse.state +
            16 * css.state +
            8 * csw.state +
            4 * cww.state +
            2 * cnw.state +
            this.state;
        ruleFrequency[stateCode] += 1;
        this.nextState = ruleset[stateCode];
    }
}

function stringToRuleset(rulestring) {
    ruleArray = new Array(512);
    for (i = 0; i < 512; i++) {
        if (parseInt(rulestring.charAt(i))) {
            ruleArray[i] = 1;
        } else {
            ruleArray[i] = 0;
        }
    }
    return ruleArray;
}

function draw(){
    var canvas = document.getElementById('canvas');
    if (canvas.getContext) {
        var context = canvas.getContext('2d');
        for (i = 0; i < world_width; i++) {
            for (j = 0; j < world_height; j++) {
                cellArray[i][j] = new Cell(i, j, Math.floor(Math.random() * 2));
            }
        }
        updateStep();
        // drawRulesetPicker();
        drawTransferArray();
        canvas.addEventListener('mousedown', (e) => {
        var rect = canvas.getBoundingClientRect();
        const pos = {
          x: (e.clientX - rect.left),
          y: (e.clientY - rect.top)
        };
        // This seems wrong, but I used this when drawing the canvas
        var i = Math.floor(pos.x/cell_size);
        var j = Math.floor(pos.y/cell_size);
        if(cellArray[i][j].state == 1){
            console.log(i,j,"was alive");
            cellArray[i][j].state = 0;
            context.fillStyle = '#ffffff';
            cellArray[i][j].update(cellArray[i][(j + 1) % world_height], cellArray[(i + 1) % world_width][(j + 1) % world_height], cellArray[(i + 1) % world_width][j], cellArray[(i + 1) % world_width][(j + world_height - 1) % world_height], cellArray[i][(j + world_height - 1) % world_height], cellArray[(i + world_width - 1) % world_width][(j + world_height - 1) % world_height], cellArray[(i + world_width - 1) % world_width][j], cellArray[(i + world_width - 1) % world_width][(j + 1) % world_height], ruleset);
        }
        else{
            console.log(i,j,"was dead");
            cellArray[i][j].state = 1;
            context.fillStyle = '#000000';
            cellArray[i][j].update(cellArray[i][(j + 1) % world_height], cellArray[(i + 1) % world_width][(j + 1) % world_height], cellArray[(i + 1) % world_width][j], cellArray[(i + 1) % world_width][(j + world_height - 1) % world_height], cellArray[i][(j + world_height - 1) % world_height], cellArray[(i + world_width - 1) % world_width][(j + world_height - 1) % world_height], cellArray[(i + world_width - 1) % world_width][j], cellArray[(i + world_width - 1) % world_width][(j + 1) % world_height], ruleset);
        }
        context.fillRect(cell_size * i, cell_size * j, cell_size, cell_size);
    });
    }
}

function startCellUpdate() {
    // creates a new interval object every time? So clear it before starting. This creates new ID every time though
    clearInterval(interval);
    interval = setInterval(updateStep, 50);
    var canvas = document.getElementById('canvas');
}

function stopCellUpdate() {
    clearInterval(interval);
}

function resetCells() {
    clearInterval(interval);
    for (i = 0; i < world_width; i++) {
        for (j = 0; j < world_height; j++) {
            cellArray[i][j].state = Math.floor(Math.random() * 2);
        }
    }
    interval = setInterval(updateStep, 50);
}

function newCode() {
    ruleset = stringToRuleset(document.getElementById("newCodeInput").value);
    drawOcterract();
    resetTransferArray();
}

function randomCode() {
    for (i = 0; i < 512; i++) {
        ruleset[i] = Math.floor(Math.random() * 2);
    }
    drawOcterract();
    resetTransferArray();
}

function updateStep() {
    var canvas = document.getElementById('canvas');
    if (canvas.getContext) {
        var context = canvas.getContext('2d');
        for (i = 0; i < world_width; i++) {
            for (j = 0; j < world_height; j++) {
                current_cell = cellArray[i][j];
                current_cell.update(cellArray[i][(j + 1) % world_height], cellArray[(i + 1) % world_width][(j + 1) % world_height], cellArray[(i + 1) % world_width][j], cellArray[(i + 1) % world_width][(j + world_height - 1) % world_height], cellArray[i][(j + world_height - 1) % world_height], cellArray[(i + world_width - 1) % world_width][(j + world_height - 1) % world_height], cellArray[(i + world_width - 1) % world_width][j], cellArray[(i + world_width - 1) % world_width][(j + 1) % world_height], ruleset);
            }
        }
        for (i = 0; i < world_width; i++) {
            for (j = 0; j < world_height; j++) {
                current_cell = cellArray[i][j];
                if (current_cell.state == 1) {
                    context.fillStyle = '#000000';
                } else {
                    context.fillStyle = '#FFFFFF';
                }
                context.fillRect(cell_size * i, cell_size * j, cell_size, cell_size);
                current_cell.state = current_cell.nextState;
            }
        }
    }
    // drawOcterract();
}

function drawRulesetPicker() { 
    rule_cell_size = 10;
    row_length = 32;
    var canvas = document.getElementById('rulesetCanvas');
    if (canvas.getContext) {
        var context = canvas.getContext('2d');
        current_ruleset_cell = 0;
        y_offset = 10;

        while(current_ruleset_cell < 512){
            for(x=0;x<row_length;x++){
                x_offset = 4 * rule_cell_size * x + rule_cell_size * x;
                context.fillStyle = '#000000';
                for(i=0;i<3;i++){
                    for(j=0;j<3;j++){
                        context.fillRect(x_offset + rule_cell_size * i, y_offset + rule_cell_size * j, rule_cell_size, rule_cell_size);
                        context.clearRect(x_offset + rule_cell_size * i + 1, y_offset + rule_cell_size * j + 1, rule_cell_size - 2, rule_cell_size - 2);
                    }
                }
                context.fillText("1", x_offset + rule_cell_size + 2 , y_offset + 4*rule_cell_size);
                current_ruleset_cell+=1;
                // console.log(x_offset,y_offset);
            }   
            y_offset += 5 * rule_cell_size;

        }
        
    }
}
function to9bit(n){
    if (n < 0 || n > 511 || n % 1 !== 0) {
        throw new Error(n + " does not fit in a byte");
    }
    return ("0000000000" + n.toString(2)).substr(-9)
}

function drawOcterract(){
    for(var i=0;i<512;i++){
        console.log(to9bit(i));
        if(ruleset[i] == 0){
            var circle = document.getElementById(to9bit(i));
            circle.style.fill = "rgb(255, 255, 255)";
        }
        else{
            var circle = document.getElementById(to9bit(i));
            circle.style.fill =  "rgb(0, 204, 102)";
        }
    }
}
function toggleCircleColor(id){
    console.log('hi');
    var circle = document.getElementById(id);
    if(circle.style.fill == "rgb(0, 204, 102)"){
        console.log("colrd");
        circle.style.fill = "rgb(255, 255, 255)";
        ruleset[parseInt(id,2)] = 0;
    }
    else{
        circle.style.fill = "rgb(0, 204, 102)";
        ruleset[parseInt(id,2)] = 1;
    }
}

function drawTransferArray(){
    var table = document.createElement("div");

    tablestring = "<td> Left to right, top to bottom display of 512 rule </td> <div> "
    for (var i = 0; i < 512; i++)  //loops through the array
    {
        val = ruleset[i].toString();
        my_id = "ta_"+ i.toString();
        tablestring += "<div id="+ my_id + " style = 'float:left; border: 1px solid black;' onClick='editTransferArrayAt("+ my_id.toString()+")'> "+ val+ " </div>";
    }
    tablestring += "</div>"
    table.innerHTML = tablestring;
    table.style.cssText += 'border: 1px solid black; border-collapse: collapse;';
    document.body.append(table);

}

function resetTransferArray(){
    for (var i = 0; i < 512; i++){
        val = ruleset[i].toString();
        var entry = document.getElementById("ta_"+i.toString());
        entry.innerText = val;
    }
}

function editTransferArrayAt(entry){
    // when rulearray is clicked, val is current value
    val = parseInt(entry.innerText);
    id = entry.id.substring(3);
    entry.innerText = (val+1)%2;
    ruleset[id] = (val+1)%2;
    // match octerracts
    if(ruleset[id] == 0){
        console.log(to9bit(parseInt(id)));
        var circle = document.getElementById(to9bit(parseInt(id)));
        circle.style.fill = "rgb(255, 255, 255)";
    }
    else{
        var circle = document.getElementById(to9bit(parseInt(id)));
        circle.style.fill =  "rgb(0, 204, 102)";
    }
}










