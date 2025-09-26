const fs = require("fs");
const args = process.argv.slice(2);
const [target, folder, name] = args;
if (fs.existsSync(folder)) {
  fs.rmSync(folder, { recursive: true, force: true });
}
fs.mkdirSync(folder);
const pathToCopy = folder + "/" + name;
fs.copyFile(target, pathToCopy, () => {});
