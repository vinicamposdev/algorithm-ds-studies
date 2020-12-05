"use strict";

process.stdin.resume();
process.stdin.setEncoding("utf-8");

let inputString = "";
let currentLine = 0;

process.stdin.on("data", (inputStdin) => {
  inputString += inputStdin;
});

process.stdin.on("end", (_) => {
  inputString = inputString
    .replace(/\s*$/, "")
    .split("\n")
    .map((str) => str.replace(/\s*$/, ""));

  main();
});

function readLine() {
  return inputString[currentLine++];
}

// Complete the miniMaxSum function below.
function miniMaxSum(arr) {
  arr.sort();
  const mini = arr[0] + arr[1] + arr[2] + arr[3];
  const arrLenght = arr.length;
  const max =
    arr[arrLenght - 1] +
    arr[arrLenght - 2] +
    arr[arrLenght - 3] +
    arr[arrLenght - 4];
  return `${mini} ${max}`;
}

function main() {
  const arr = readLine()
    .split(" ")
    .map((arrTemp) => parseInt(arrTemp, 10));

  console.log(miniMaxSum(arr));
}
