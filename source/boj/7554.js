const fs = require('fs');
const input = fs.readFileSync(0, 'utf8').trim().split('\n');

const n = parseInt(input[0]);
for (let i = 1; i <= n; i++) {
  const arr = input[i].split(' ').map(Number);
  // console.log(arr);
  let count = 0;
  for (let j = 1; j <= arr[0]; j++) {
    for (let k = 1; k <= arr[0] - 1; k++) {
      if (arr[k] > arr[k + 1]) {
        count += 1;
        const tmp = arr[k];
        arr[k] = arr[k + 1];
        arr[k + 1] = tmp;
      }
    }
  }
  console.log(`Scenario #${i}:`);
  console.log(count);
  console.log();
}