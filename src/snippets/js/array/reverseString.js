const recursive = (str) => str === "" ? "" : recursive(str.substr(1)) + str.charAt(0);

const builtInFunction = (str) => str.split("").reverse().join("");
