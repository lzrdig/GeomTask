using System;
using System.Drawing;
using System.Windows.Forms;

using SharpGL;
using SharpGL.SceneGraph;
using SharpGL.SceneGraph.Core;
using SharpGL.SceneGraph.Lighting;
using SharpGL.SceneGraph.Effects;
using SharpGL.SceneGraph.Quadrics;
using System.Collections.ObjectModel;

namespace SceneSample
{
    public partial class FormSceneSample : Form
    {
        private Point mMouseLeftBtnPos = new Point();
        private ArcBallEffect arcBallEffect = new ArcBallEffect();
        private float m_xRotate;
        private float m_yRotate;
        private double m_dZoomOldVal;

        /// <summary>
        /// Initializes a new instance of the <see cref="FormSceneSample"/> class.
        /// </summary>
        public FormSceneSample()
        {
            InitializeComponent();

            ptPosX.Text = "0.0";
            ptPosY.Text = "3.0";
            ptPosZ.Text = "0.0";

            bottomPosX.Text = "0.0";
            bottomPosY.Text = "0.0";
            bottomPosZ.Text = "0.0";

            topPosX.Text = "0.0";
            topPosY.Text = "0.0";
            topPosZ.Text = "1.0";

            baseRadius.Text = "0.5";

            zoomScale.Value = 5;
            m_dZoomOldVal = 5.0;

            sceneControl1.MouseDown += new MouseEventHandler(FormSceneSample_MouseDown);
            sceneControl1.MouseMove += new MouseEventHandler(FormSceneSample_MouseMove);
            sceneControl1.MouseUp += new MouseEventHandler(sceneControl1_MouseUp);

            //  Add some design-time primitives.
            sceneControl1.Scene.SceneContainer.AddChild(new
                SharpGL.SceneGraph.Primitives.Grid());
            sceneControl1.Scene.SceneContainer.AddChild(new 
                SharpGL.SceneGraph.Primitives.Axies());

            //  Create a light.
            Light light = new Light()
            {
                On = true,
                Position = new Vertex(3, 10, 3),
                GLCode = OpenGL.GL_LIGHT0
            };

            //  Add the light.
            sceneControl1.Scene.SceneContainer.AddChild(light);

            DrawCylAndPoint();

            //  Add the root element to the tree control.
            AddElementToTree(sceneControl1.Scene.SceneContainer, treeView1.Nodes);

            sceneControl1.Scene.RenderBoundingVolumes = false;

            sceneControl1.OpenGL.Scale(1.5, 1.5, 1.5);
        }

        #region Mouse Handlers
        void sceneControl1_MouseUp(object sender, MouseEventArgs e)
        {
            arcBallEffect.ArcBall.MouseUp(e.X, e.Y);
        }

        void FormSceneSample_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                //arcBallEffect.ArcBall.MouseMove(e.X, e.Y);

                Point rotate = new Point( mMouseLeftBtnPos.X - e.Location.X, mMouseLeftBtnPos.Y - e.Location.Y);
                mMouseLeftBtnPos = e.Location;

                m_yRotate -= rotate.X;
                m_xRotate -= rotate.Y;

                sceneControl1.OpenGL.Rotate(
                    (float)rotate.X / 20, 
                    (float)rotate.Y / 2, -(float)rotate.X / 2);
            }
        }

        void FormSceneSample_MouseDown(object sender, MouseEventArgs e)
        {
            arcBallEffect.ArcBall.SetBounds(sceneControl1.Width, sceneControl1.Height);
            arcBallEffect.ArcBall.MouseDown(e.X, e.Y);
            mMouseLeftBtnPos = e.Location;
        }
        #endregion

        #region Tree control Handlers
        private void AddElementToTree(SceneElement sceneElement, TreeNodeCollection nodes)
        {
            //  Add the element.
            TreeNode newNode = new TreeNode() 
            { 
                Text = sceneElement.Name, 
                Tag = sceneElement 
            };
            nodes.Add(newNode);

            //  Add each child.
            foreach (var element in sceneElement.Children)
                AddElementToTree(element, newNode.Nodes);
        }

        /// <summary>
        /// Handles the AfterSelect event of the treeView1 control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.Windows.Forms.TreeViewEventArgs"/> instance containing the event data.</param>
        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            SelectedSceneElement = e.Node.Tag as SceneElement;
        }

        /// <summary>
        /// Called when [selected scene element changed].
        /// </summary>
        private void OnSelectedSceneElementChanged()
        {
            propertyGrid1.SelectedObject = SelectedSceneElement;
        }
        #endregion

        /// <summary>
        /// The selected scene element.
        /// </summary>
        private SceneElement selectedSceneElement = null;

        /// <summary>
        /// Gets or sets the selected scene element.
        /// </summary>
        /// <value>
        /// The selected scene element.
        /// </value>
        public SceneElement SelectedSceneElement
        {
            get { return selectedSceneElement; }
            set
            {
                selectedSceneElement = value;
                OnSelectedSceneElementChanged();
            }
        }

        private void ZoomChanged(object sender, EventArgs e)
        {
            var newZoomVal = ((TrackBar)sender).Value;
            if(m_dZoomOldVal!=0)
                sceneControl1.OpenGL.Scale(5.0f / m_dZoomOldVal, 5.0f / m_dZoomOldVal, 5.0f / m_dZoomOldVal);
            sceneControl1.OpenGL.Scale(newZoomVal / 5.0f, newZoomVal / 5.0f, newZoomVal / 5.0f);
            m_dZoomOldVal = newZoomVal;
        }

        private void UpdateRadius(object sender, EventArgs e)
        {

        }

        private void UpdateCylinder(object sender, EventArgs e)
        {
            ObservableCollection<SceneElement> tmp = sceneControl1.Scene.SceneContainer.Children;
            Cylinder cyl;
            Disk bottomCylCap;

            // reset the cylinder and point object (remove and put back into the scene
            // in the initial position
            sceneControl1.Scene.SceneContainer.RemoveChild(tmp[7]);
            sceneControl1.Scene.SceneContainer.RemoveChild(tmp[6]);
            sceneControl1.Scene.SceneContainer.RemoveChild(tmp[5]);

            // apply new translations and rotations
            tmp = sceneControl1.Scene.SceneContainer.Children;

            if (tmp.Count > 6)
            {
                cyl = (Cylinder)tmp[5];

                cyl.BaseRadius = Double.Parse(baseRadius.Text);
                cyl.TopRadius = Double.Parse(baseRadius.Text);

                var dx = Convert.ToDouble(topPosX.Text) - Convert.ToDouble(bottomPosX.Text);
                var dy = Convert.ToDouble(topPosY.Text) - Convert.ToDouble(bottomPosY.Text);
                var dz = Convert.ToDouble(topPosZ.Text) - Convert.ToDouble(bottomPosZ.Text);
                var cylHeight = Math.Sqrt(dx * dx + dy * dy + dz * dz);

                var angZ = 57.2957795 * Math.Acos(dz / cylHeight);
                var angY = 0.0;
                var xyComp = Math.Sqrt(cylHeight * cylHeight - dz * dz);
                if (xyComp != 0.0)
                {
                    angY = 57.2957795 * Math.Acos(dx / xyComp);

                    //cyl.Transformation.RotateY = (float)angZ;
                    cyl.Transformation.RotateZ = (float)angY;
                }

                // update the cylinder
                cyl.Height = cylHeight;
                cyl.Transformation.TranslateX = float.Parse(bottomPosX.Text);
                cyl.Transformation.TranslateY = float.Parse(bottomPosY.Text);
                cyl.Transformation.TranslateZ = float.Parse(bottomPosZ.Text);


                // update the cylinder top cap
                bottomCylCap = (Disk)tmp[6];

                bottomCylCap.OuterRadius = Double.Parse(baseRadius.Text);
                bottomCylCap.Transformation.TranslateX = float.Parse(bottomPosX.Text);
                bottomCylCap.Transformation.TranslateY = float.Parse(bottomPosY.Text);
                bottomCylCap.Transformation.TranslateZ = float.Parse(bottomPosZ.Text);
                bottomCylCap.Transformation.RotateY = (float)angZ;
                bottomCylCap.Transformation.RotateZ = (float)angY;
            }

        }


        private void DrawCylAndPoint()
        {            
            var dx = Convert.ToDouble(topPosX.Text) - Convert.ToDouble(bottomPosX.Text);
            var dy = Convert.ToDouble(topPosY.Text) - Convert.ToDouble(bottomPosY.Text);
            var dz = Convert.ToDouble(topPosZ.Text) - Convert.ToDouble(bottomPosZ.Text);
            var cylHeight = Math.Sqrt(dx * dx + dy * dy + dz * dz);                        
            var xyProjComp = Math.Sqrt(dx*dx +dy*dy);

            var gl = sceneControl1.OpenGL;

            var angZ = 57.2957795 * Math.Acos(dz / cylHeight);
            var angY = 0.0;
            if (xyProjComp != 0.0)
                angY = 57.2957795 * Math.Acos(dx / xyProjComp);

            // order of rotation will be Yaw, Pitch, roll. Yaw is = 0
            // Yaw is rotation around X axis, Pitch - around Y axiz
            var pitchAng = -Math.Asin((dz / cylHeight) * (dx / xyProjComp));
            var rollAng = Math.Atan(Math.Sin(angY)/ Math.Tan(angZ));

            //  Create a cylinder body.
            Cylinder cyl = new Cylinder();
            cyl.BaseRadius = Convert.ToDouble(baseRadius.Text);
            cyl.Slices = 16;
            cyl.Stacks = 16;
            cyl.Height = cylHeight;
            cyl.TopRadius = cyl.BaseRadius;
            cyl.Transformation.RotateY = (float)pitchAng;
            //cyl.Transformation.RotateX = (float)angZ;
            cyl.Transformation.RotateZ = (float)rollAng;
            cyl.Transformation.TranslateX = float.Parse(bottomPosX.Text);
            cyl.Transformation.TranslateY = float.Parse(bottomPosY.Text);
            cyl.Transformation.TranslateZ = float.Parse(bottomPosZ.Text);

            //  Add it.
            sceneControl1.Scene.SceneContainer.AddChild(cyl);




            //  Create a cylinder's bottom cap. Not working as a SceneElement,
            // since the disk is not an "object". It is flat
            Disk bottomCylCap = new Disk();
            bottomCylCap.InnerRadius = 0;
            bottomCylCap.OuterRadius = cyl.BaseRadius;
            bottomCylCap.Transformation.TranslateX = float.Parse(bottomPosX.Text);
            bottomCylCap.Transformation.TranslateY = float.Parse(bottomPosY.Text);
            bottomCylCap.Transformation.TranslateZ = float.Parse(bottomPosZ.Text);
            cyl.Transformation.RotateY = (float)pitchAng;
            //cyl.Transformation.RotateX = (float)angZ;
            cyl.Transformation.RotateZ = (float)rollAng;

            //  Add it.
            sceneControl1.Scene.SceneContainer.AddChild(bottomCylCap);




            //  Create a cylinder's top cap. Not working as a SceneElement,
            // since the disk is not an "object". It is flat
            Disk topCylCap = new Disk();
            topCylCap.InnerRadius = 0;
            topCylCap.OuterRadius = cyl.BaseRadius;
            cyl.Transformation.RotateY = (float)pitchAng;
            //cyl.Transformation.RotateX = (float)angZ;
            cyl.Transformation.RotateZ = (float)rollAng;
            topCylCap.Transformation.TranslateX = float.Parse(topPosX.Text);
            topCylCap.Transformation.TranslateY = float.Parse(topPosY.Text);
            topCylCap.Transformation.TranslateZ = float.Parse(topPosZ.Text);

            //  Add it.
            sceneControl1.Scene.SceneContainer.AddChild(topCylCap);




            // Create the test 3D point represented as a phere
            Sphere testPt = new Sphere();
            testPt.Radius = 0.1;
            testPt.Transformation.TranslateX = float.Parse(ptPosX.Text);
            testPt.Transformation.TranslateY = float.Parse(ptPosY.Text);
            testPt.Transformation.TranslateZ = float.Parse(ptPosZ.Text);

            sceneControl1.Scene.SceneContainer.AddChild(testPt);
        }

        private void RedrawCylinder(object sender, EventArgs e)
        {
            var tmp = sceneControl1.Scene.SceneContainer.Children;


            for (int i = 0; i < 4; i++)
            {
                if (tmp.Count > 5) sceneControl1.Scene.SceneContainer.RemoveChild(tmp[tmp.Count - 1]);
            }

            DrawCylAndPoint();
        }
    }
}