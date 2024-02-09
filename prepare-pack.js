const fs = require("fs");
const path = require("path");
const args = process.argv.slice(2);
const [target, folder, name] = args;
if (fs.existsSync(folder)) {
  fs.rmSync(folder, { recursive: true, force: true });
}
fs.mkdirSync(folder);
const pathToNode = path.join(__dirname, target);
const pathToCopy = folder + "\\" + name;
console.log(pathToCopy);
fs.copyFile(pathToNode, pathToCopy, () => {});
