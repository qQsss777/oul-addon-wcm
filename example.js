const addon = require("./build/Release/WCMAccessor");
try {
  const date = new Date().toDateString();
  const pwd = date.replace(/\s/g, "");
  console.log(pwd);
  const success = addon.setCredentials("toto", "test", pwd);
  console.log(success);
  const crdP = addon.getCredentials("toto");
  console.log(crdP);
} catch (error) {
  console.log("erreur");
  console.log(error);
}
