import fs from "fs/promises";

const rawFile = await fs.readFile("./package.json", { encoding: "utf-8" });
const jsonFile = JSON.parse(rawFile);
delete jsonFile["scripts"];
delete jsonFile["devDependencies"];
await fs.writeFile("./package.json", JSON.stringify(jsonFile, null, 2));
