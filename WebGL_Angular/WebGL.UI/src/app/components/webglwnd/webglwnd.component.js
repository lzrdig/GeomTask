"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};
Object.defineProperty(exports, "__esModule", { value: true });
var core_1 = require("@angular/core");
var THREE = require("three");
var three_orbitcontrols_ts_1 = require("three-orbitcontrols-ts");
var WebglwndComponent = /** @class */ (function () {
    function WebglwndComponent() {
        this.renderer = new THREE.WebGLRenderer();
        this.scene = null;
        this.camera = null;
        this.materials = null;
        this.controls = null;
        this.cylinder = {
            bottomCtr: {
                X: 0.0,
                Y: 0.0,
                Z: 0.0
            },
            topCtr: {
                X: 0.0,
                Y: 0.0,
                Z: 200.0
            },
            baseRadius: 100,
            cylHeight: 0.0,
            calculateHeight: function () {
                var dx = Math.abs(this.topCtr.X - this.bottomCtr.X);
                var dy = Math.abs(this.topCtr.Y - this.bottomCtr.Y);
                var dz = Math.abs(this.topCtr.Z - this.bottomCtr.Z);
                this.cylHeight = Math.sqrt(dx * dx + dy * dy + dz * dz);
                return this.cylHeight;
            },
            calculateRotation: function () {
            }
        };
        this.testpt = { X: 200, Y: 100, Z: 500 };
        this.cylinderGLobj = null;
        this.sphereGLobj = null;
        this.scene = new THREE.Scene();
        //camera
        this.camera = new THREE.PerspectiveCamera(75, 600 / 400, 1, 10000);
        this.camera.position.z = 1000;
        // controls
        this.controls = new three_orbitcontrols_ts_1.OrbitControls(this.camera, this.renderer.domElement);
        this.controls.addEventListener('change', this.renderScene);
        // light
        var light = new THREE.DirectionalLight(0xffffff);
        light.position.set(0, 1, 1).normalize();
        this.scene.add(light);
        // ambient light
        var ambient = new THREE.AmbientLight(0x555555);
        this.scene.add(ambient);
        // axes
        var axis = new THREE.AxisHelper(600);
        axis.position.set(0, 0, 0);
        //axis.rotation.x = Math.PI/4;
        this.scene.add(axis);
        // grid (floor)
        var gridXY = new THREE.GridHelper(800, 10);
        gridXY.position.set(0, 0, 0);
        gridXY.rotation.x = Math.PI / 2;
        gridXY.setColors(new THREE.Color(0x000000), new THREE.Color(0x000066));
        this.scene.add(gridXY);
        var dx = this.cylinder.topCtr.X - this.cylinder.bottomCtr.X;
        var dy = this.cylinder.topCtr.Y - this.cylinder.bottomCtr.Y;
        var dz = this.cylinder.topCtr.Z - this.cylinder.bottomCtr.Z;
        var cylHeight = Math.sqrt(dx * dx + dy * dy + dz * dz);
        var cylRadius = this.cylinder.baseRadius;
        var cylindergeometry = new THREE.CylinderGeometry(cylRadius, cylRadius, cylHeight, 16, 16, false);
        var cylinderMaterial = new THREE.MeshLambertMaterial({ color: 0x000088 });
        this.cylinderGLobj = new THREE.Mesh(cylindergeometry, cylinderMaterial);
        this.cylinderGLobj.position.set(this.cylinder.bottomCtr.X, this.cylinder.bottomCtr.Y, this.cylinder.bottomCtr.Z);
        this.cylinderGLobj.rotation.x = Math.PI / 2;
        this.scene.add(this.cylinderGLobj);
        // Sphere parameters: radius, segments along width, segments along height 
        var spheregeometry = new THREE.SphereGeometry(15, 32, 16);
        var sphereMaterial = new THREE.MeshLambertMaterial({ color: 0x8888ff });
        this.sphereGLobj = new THREE.Mesh(spheregeometry, sphereMaterial);
        this.sphereGLobj.position.set(this.testpt.X, this.testpt.Y, this.testpt.Z);
        this.scene.add(this.sphereGLobj);
    }
    WebglwndComponent.prototype.ngOnInit = function () { };
    WebglwndComponent.prototype.ngAfterViewInit = function () {
        this.renderer.setSize(600, 400);
        this.renderer.domElement.style.display = "block";
        this.renderer.domElement.style.margin = "auto";
        this.rendererContainer.nativeElement.appendChild(this.renderer.domElement);
        this.animate();
    };
    WebglwndComponent.prototype.animate = function () {
        var _this = this;
        window.requestAnimationFrame(function () { return _this.animate(); });
        this.updateScene();
        this.renderScene();
    };
    WebglwndComponent.prototype.renderScene = function () {
        this.renderer.render(this.scene, this.camera);
    };
    WebglwndComponent.prototype.updateScene = function () {
        this.cylinderGLobj.position.set(this.cylinder.bottomCtr.X, this.cylinder.bottomCtr.Y, this.cylinder.bottomCtr.Z);
        this.cylinderGLobj.baseRadius = this.cylinder.baseRadius;
        this.sphereGLobj.position.set(this.testpt.X, this.testpt.Y, this.testpt.Z);
    };
    __decorate([
        core_1.ViewChild('rendererContainer'),
        __metadata("design:type", core_1.ElementRef)
    ], WebglwndComponent.prototype, "rendererContainer", void 0);
    WebglwndComponent = __decorate([
        core_1.Component({
            selector: 'webglwnd',
            templateUrl: './webglwnd.component.html',
            styleUrls: ['./webglwnd.component.scss']
        }),
        __metadata("design:paramtypes", [])
    ], WebglwndComponent);
    return WebglwndComponent;
}());
exports.WebglwndComponent = WebglwndComponent;
//# sourceMappingURL=C:/Users/Dorel/Source/Repos/GeomTask/WebGL_Angular/WebGL.UI/src/app/components/webglwnd/webglwnd.component.js.map