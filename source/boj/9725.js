const fs = require('fs');
const input = fs.readFileSync(0, 'utf8').trim().split('\n');
input.reverse();

const T = Number(input.pop());
for (let t = 0; t < T; t++) {
  const n = Number(input.pop());
  const arr = input.pop().split(' ').map((x) => { return Number(x) % 3 });
  let ans1 = 0;
  for (let i = 0; i < n; i += 3) {
    if (arr[i] != 0) {
      let swapped = false;
      for (let j = 0; j < n; j++) {
        if (j % 3 == arr[i] && arr[j] == 0) {
          arr[j] = arr[i];
          arr[i] = 0;
          swapped = true;
          break;
        }
      }
      if (!swapped) {
        for (let j = 0; j < n; j++) {
          if (j % 3 != 0 && arr[j] == 0) {
            arr[j] = arr[i];
            arr[i] = 0;
            break;
          }
        }
      }
      ans1++;
    }
  }
  const initial = 0;
  const ans2 = arr.reduce((pre, cur, idx) => { return pre + (idx % 3 != cur); }, 0);
  console.log(`Case #${t + 1}: ${ans1 + ans2 / 2}`);
}