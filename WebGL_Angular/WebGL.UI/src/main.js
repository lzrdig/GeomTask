"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
require("./polyfills.ts");
var platform_browser_dynamic_1 = require("@angular/platform-browser-dynamic");
var core_1 = require("@angular/core");
var environment_1 = require("./environments/environment");
var app_module_1 = require("./app/app.module");
if (environment_1.environment.production) {
    core_1.enableProdMode();
}
platform_browser_dynamic_1.platformBrowserDynamic().bootstrapModule(app_module_1.AppModule);
//# sourceMappingURL=C:/Users/Dorel/Source/Repos/GeomTask/WebGL_Angular/WebGL.UI/src/main.js.map