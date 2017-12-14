"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var start_component_1 = require("./components/start/start.component");
var webglwnd_component_1 = require("./components/webglwnd/webglwnd.component");
exports.routerConfig = [
    { path: 'start', component: start_component_1.StartComponent },
    { path: 'webgl', component: webglwnd_component_1.WebglwndComponent },
    { path: '', redirectTo: '/start', pathMatch: 'full' },
    { path: '**', redirectTo: '/start', pathMatch: 'full' }
];
//# sourceMappingURL=C:/Users/Dorel/Source/Repos/GeomTask/WebGL_Angular/WebGL.UI/src/app/app.routing.js.map