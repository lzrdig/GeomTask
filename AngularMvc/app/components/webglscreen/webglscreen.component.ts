import { Component, ViewChild, ElementRef } from '@angular/core';
import { OrbitControls } from 'three-orbitcontrols-ts';
import * as THREE from 'three';



@Component({
    // tslint:disable-next-line:component-selector
    selector: 'webgl-screen',
    templateUrl: '/app//components//webglscreen//webglscreen.component.html'
})
export class WebGlComponent {
    title: "WebGL"

    @ViewChild('rendererContainer') rendererContainer: ElementRef;

    renderer = new THREE.WebGLRenderer();
    scene = null;
    camera = null;
    materials = null;
    controls = null;


    trgtpt = { X: 200, Y: 100, Z: 500 };
    testpt = { X: 0.0, Y: 0.0, Z: 500 };
    cylinder = {
        bottomCtr:{
            X: 0.0,
            Y: 0.0,
            Z: 0.0
        },
        topCtr:{
            X: 0.0,
            Y: 0.0,
            Z: 200.0
        },
        axis: {
            dX: 0.0,
            dY: 0.0,
            dZ: 0.0
        },
        baseRadius:100,
        height:0.0,
        rotation: {
            angX: 0.0,
            angY: 0.0,
            angZ: 0.0
        },
        calculateAxis() {
            this.axis.dX = this.topCtr.X - this.bottomCtr.X;
            this.axis.dY = this.topCtr.Y - this.bottomCtr.Y;
            this.axis.dZ = this.topCtr.Z - this.bottomCtr.Z;

            return this.axis;
        },
        calculateHeight():number{
            var dx = this.topCtr.X - this.bottomCtr.X;
            var dy = this.topCtr.Y - this.bottomCtr.Y;
            var dz = this.topCtr.Z - this.bottomCtr.Z;
            this.height = Math.sqrt(dx * dx + dy * dy + dz * dz);

            return this.height;
        },
        calculateEulerAnglesFromZ(): void{
            // Assumption is that cylinder is initially set with the bottom point at the (0,0,0) position and points up along Z axis.
            // This calculates the "Euler" angles needed to "transofrm" cylinder's axis vector v1 = (0,0,1) when pointing up along Z axis 
            // into the vector v2 = (topCtr.X - bottomCtr.X, topCtr.Y - bottomCtr.Y, topCtr.Z - bottomCtr.Z)
            var dx = this.topCtr.X - this.bottomCtr.X;
            var dy = this.topCtr.Y - this.bottomCtr.Y;
            var dz = this.topCtr.Z - this.bottomCtr.Z;

            this.height = Math.sqrt(dx * dx + dy * dy + dz * dz);
            var v2 = new THREE.Vector3(dx / this.height, dy / this.height, dz / this.height);

            var cylHeight = this.height;

            var xyProjComp = Math.sqrt(dx * dx + dy * dy);

            var angZ = (180 / Math.PI) * Math.acos(dz / cylHeight);
            var angY = 0.0;
            var pitchAng = 0.0, rollAng = 0.0;
            if (xyProjComp != 0.0) {
                angY = (180 / Math.PI) * Math.acos(dx / xyProjComp);

                // order of rotation will be Yaw, Pitch, roll. Yaw is = 0
                // Yaw is rotation around X axis, Pitch - around Y axiz, , Roll - around Y axiz           

                if ((dz / cylHeight) * (dx / xyProjComp) == 0.0)
                    pitchAng = 0.0;
                else
                    pitchAng = -Math.asin((dz / cylHeight) * (dx / xyProjComp));
                if (angY == 0.0 || Math.tan(angZ) == 0.0)
                    rollAng = 0.0;
                else
                    rollAng = Math.atan(Math.sin(angY) / Math.tan(angZ));
            }


            this.rotation.X = -dy * dz;
            this.rotation.Y = dx * dz;
            this.rotation.Z = 0;
        },
        alignAxisViaRotation(): THREE.Quaternion {
            var dx = this.topCtr.X - this.bottomCtr.X;
            var dy = this.topCtr.Y - this.bottomCtr.Y;
            var dz = this.topCtr.Z - this.bottomCtr.Z;
            var norm = Math.sqrt(dx * dx + dy * dy + dz * dz);

            var v1 = new THREE.Vector3(0, 0, 1);
            var v2 = new THREE.Vector3(dx / norm, dy / norm, dz / norm);

            var a = new THREE.Vector3(0, 0, 1);
            a.cross(v2);

            var q = new THREE.Quaternion;

            q.setFromUnitVectors(v1, v2);   

            return q;
        }
      };

    cylinderGLobj = null;
    sphereGLobj = null;


    constructor() {
        this.scene = new THREE.Scene();

        //camera
        this.camera = new THREE.PerspectiveCamera(75, 600 / 400, 1, 10000);
        this.camera.position.z = 1000;
        this.camera.position.y = 500;

        // controls
        this.controls = new OrbitControls(this.camera, this.renderer.domElement);
        this.controls.addEventListener('change', this.renderScene);

        // light
        var light = new THREE.DirectionalLight(0xffffff);
        light.position.set(0, 1, 1).normalize();
        this.scene.add(light);

        // ambient light
        var ambient = new THREE.AmbientLight(0x555555);
        this.scene.add(ambient);

        // axes
        var axis = new THREE.AxisHelper(600)
        axis.position.set(0, 0, 0);
        this.scene.add(axis);

        // grid (floor)
        var gridXY = new THREE.GridHelper(800, 10, 0x000066, 0x000066);
        gridXY.position.set(0, 0, 0);
        gridXY.rotation.x = Math.PI / 2;
        this.scene.add(gridXY);

        // Cylinder object
        var cylHeight = this.cylinder.calculateHeight();
        var cylRadius = this.cylinder.baseRadius;
        var cylQ = this.cylinder.alignAxisViaRotation();
        this.cylinder.calculateAxis();
        var cylindergeometry = new THREE.CylinderGeometry(cylRadius, cylRadius, cylHeight, 16, 16, false);
        cylindergeometry.name = "Cylinder";
        var cylinderMaterial = new THREE.MeshLambertMaterial({ color: 0xf00088 });
        this.cylinderGLobj = new THREE.Mesh(cylindergeometry, cylinderMaterial); 
        //this.cylinderGLobj.setRotationFromQuaternion(cylQ);
        this.cylinderGLobj.position.set(this.cylinder.bottomCtr.X + this.cylinder.axis.dX / 2, this.cylinder.bottomCtr.Y + this.cylinder.axis.dY / 2, this.cylinder.bottomCtr.Z + this.cylinder.axis.dZ / 2);
        //this.cylinderGLobj.position.set(this.cylinder.bottomCtr.X - this.cylinder.axis.dX / 2, this.cylinder.bottomCtr.Y - this.cylinder.axis.dY / 2, this.cylinder.bottomCtr.Z - this.cylinder.axis.dZ / 2);
        //this.cylinderGLobj.position.set(this.cylinder.bottomCtr.X, this.cylinder.bottomCtr.Y, this.cylinder.bottomCtr.Z);
        this.cylinderGLobj.rotation.x = Math.PI / 2;
        //this.cylinderGLobj.setRotationFromQuaternion(cylQ);
        this.scene.add(this.cylinderGLobj);

        // Sphere parameters: radius, segments along width, segments along height 
        var spheregeometry = new THREE.SphereGeometry(15, 32, 16);
        var sphereMaterial = new THREE.MeshLambertMaterial({ color: 0x8888ff });
        this.sphereGLobj = new THREE.Mesh(spheregeometry, sphereMaterial);
        this.sphereGLobj.position.set(this.testpt.X, this.testpt.Y, this.testpt.Z);
        this.sphereGLobj.rotation.x = Math.PI / 2;
        this.scene.add(this.sphereGLobj);
    }


    ngAfterViewInit() {
        this.renderer.setSize(600, 400);
        this.renderer.domElement.style.display = "block";
        this.renderer.domElement.style.margin = "auto";
        this.rendererContainer.nativeElement.appendChild(this.renderer.domElement);

        this.animate();
    }

    animate() {
        window.requestAnimationFrame(() => this.animate());

        this.updateScene();

        this.renderScene();
    }

    renderScene() {
        if(this.renderer != null)
            this.renderer.render(this.scene, this.camera);
    }

    updateScene() {
        //this.cylinderGLobj.position.set(this.cylinder.bottomCtr.X, this.cylinder.bottomCtr.Y, this.cylinder.bottomCtr.Z + this.cylinder.height/2)

        this.sphereGLobj.position.set(this.testpt.X, this.testpt.Y, this.testpt.Z);
    }

    topctrZvaluechange($event) {
        var newTopZ = this.cylinder.topCtr.Z;
        if(typeof $event == "number") newTopZ = $event;
        this.cylinder.topCtr.Z = newTopZ;

        var cylHeight = this.cylinder.calculateHeight();
        var cylRadius = this.cylinder.baseRadius;    
        
        this.updateCylinder(this.cylinder);
    }

    topctrYvaluechange($event) {
        var newTopY = this.cylinder.topCtr.Y;
        if(typeof $event == "number") newTopY = $event;
        this.cylinder.topCtr.Y = newTopY;

        var cylHeight = this.cylinder.calculateHeight();
        var cylRadius = this.cylinder.baseRadius;    
        
        this.updateCylinder(this.cylinder);
    }

    topctrXvaluechange($event) {
        var newTopX = this.cylinder.topCtr.X;
        if(typeof $event == "number") newTopX = $event;
        this.cylinder.topCtr.X = newTopX;

        var cylHeight = this.cylinder.calculateHeight();
        var cylRadius = this.cylinder.baseRadius;    
        
        this.updateCylinder(this.cylinder);
    }

    bottomctrZvaluechange($event) {
        var newBotZ = this.cylinder.bottomCtr.Z;
        if (typeof $event == "number") newBotZ = $event;
        this.cylinder.bottomCtr.Z = newBotZ;

        var cylHeight = this.cylinder.calculateHeight();
        var cylRadius = this.cylinder.baseRadius;

        this.updateCylinder(this.cylinder);
    }

    bottomctrYvaluechange($event) {
        var newBotY = this.cylinder.bottomCtr.Y;
        if (typeof $event == "number") newBotY = $event;
        this.cylinder.bottomCtr.Y = newBotY;

        var cylHeight = this.cylinder.calculateHeight();
        var cylRadius = this.cylinder.baseRadius;

        this.updateCylinder(this.cylinder);
    }

    bottomctrXvaluechange($event) {
        var newBotX = this.cylinder.bottomCtr.X;
        if (typeof $event == "number") newBotX = $event;
        this.cylinder.bottomCtr.X = newBotX;

        var cylHeight = this.cylinder.calculateHeight();
        var cylRadius = this.cylinder.baseRadius;

        this.updateCylinder(this.cylinder);
    }

    radiusvaluechange($event) {
        var cylHeight = this.cylinder.calculateHeight();
        var cylRadius = this.cylinder.baseRadius;

        if(typeof $event == "number") cylRadius = $event;

        this.cylinder.baseRadius = cylRadius;

        this.updateCylinder(this.cylinder);        
    }

    updateCylinder(cylObjNew:any){
         var sceneChildren = this.scene.children.filter(child => child.hasOwnProperty('geometry'));
         var cylObj = sceneChildren.filter(geom => geom.geometry.name === "Cylinder");    
        // this.scene.remove(cylObj);    //this does not work for some reason  

        var ax = this.cylinder.calculateAxis();

        this.scene.remove(this.cylinderGLobj);        

        var cylindergeometry = new THREE.CylinderGeometry(cylObjNew.baseRadius, cylObjNew.baseRadius, cylObjNew.height, 16, 16, false);
        cylindergeometry.name = "Cylinder";  
        
        //this.cylinderGLobj.position.set(this.cylinder.bottomCtr.X, this.cylinder.bottomCtr.Y, this.cylinder.bottomCtr.Z + cylObjNew.height / 2);
        //this.cylinderGLobj.position.set(this.cylinder.bottomCtr.X - this.cylinder.axis.dX / 2, this.cylinder.bottomCtr.Y - this.cylinder.axis.dY / 2, this.cylinder.bottomCtr.Z - this.cylinder.axis.dZ / 2);
        //this.cylinderGLobj.position.set(this.cylinder.bottomCtr.X + this.cylinder.axis.dX / 2, this.cylinder.bottomCtr.Y + this.cylinder.axis.dY / 2, this.cylinder.bottomCtr.Z + this.cylinder.axis.dZ / 2);

        var cylinderMaterial = new THREE.MeshLambertMaterial({ color: 0xf00088 });
        this.cylinderGLobj = new THREE.Mesh(cylindergeometry, cylinderMaterial);

        this.cylinderGLobj.rotation.x = Math.PI / 2;

        var q = this.cylinder.alignAxisViaRotation();

        var ax1 = new THREE.Vector3();
        //ax1 = ax1.applyQuaternion(q);
        
        ax1 = ax1.applyAxisAngle(new THREE.Vector3(1,0,0), Math.PI / 2);

        var translation = {
            X: this.cylinder.bottomCtr.X + ax1.x / 2,
            Y: this.cylinder.bottomCtr.Y + ax1.y / 2,
            Z: this.cylinder.bottomCtr.Z + ax1.y / 2
        }
        this.cylinderGLobj.position.set(translation.X, translation.Y, translation.Z);

        //this.cylinderGLobj.position.set(this.cylinder.bottomCtr.X + this.cylinder.axis.dX, this.cylinder.bottomCtr.Y + this.cylinder.axis.dY, this.cylinder.bottomCtr.Z + this.cylinder.axis.dZ);
        

        //this.cylinderGLobj.setRotationFromQuaternion(this.cylinder.alignAxisViaRotation());

        this.scene.add(this.cylinderGLobj);
    }
}