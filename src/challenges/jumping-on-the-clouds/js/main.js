function jumpingOnClouds(n,c) {
    let path=0
    for(let i = 0; i<n-1;i++) {
        if(!c[i+2]){
            i++
        }        
        path ++
    }
    return path
}
  
(main = () => {
    const n = 6;
    const ar = [0, 0, 0, 0, 1, 0];
    const output = 3
    jumpingOnClouds(n, ar);
    if(jumpingOnClouds(n, ar) === output) {
        console.log(true)
    } else console.log(false)
})();
  