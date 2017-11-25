namespace SceneSample
{
    partial class FormSceneSample
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormSceneSample));
            this.sceneControl1 = new SharpGL.SceneControl();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.propertyGrid1 = new System.Windows.Forms.PropertyGrid();
            this.panel3 = new System.Windows.Forms.Panel();
            this.label7 = new System.Windows.Forms.Label();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.zoomScale = new System.Windows.Forms.TrackBar();
            this.trackBar1 = new System.Windows.Forms.TrackBar();
            this.panel2 = new System.Windows.Forms.Panel();
            this.updateBtn = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.baseRadius = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.topPosZ = new System.Windows.Forms.TextBox();
            this.topPosY = new System.Windows.Forms.TextBox();
            this.topPosX = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.bottomPosZ = new System.Windows.Forms.TextBox();
            this.bottomPosY = new System.Windows.Forms.TextBox();
            this.bottomPosX = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.ptPosZ = new System.Windows.Forms.TextBox();
            this.ptPosY = new System.Windows.Forms.TextBox();
            this.ptPosX = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.sceneControl1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            this.panel3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.zoomScale)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
            this.panel2.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // sceneControl1
            // 
            this.sceneControl1.DrawFPS = false;
            this.sceneControl1.Location = new System.Drawing.Point(0, 0);
            this.sceneControl1.Name = "sceneControl1";
            this.sceneControl1.OpenGLVersion = SharpGL.Version.OpenGLVersion.OpenGL2_1;
            this.sceneControl1.RenderContextType = SharpGL.RenderContextType.DIBSection;
            this.sceneControl1.RenderTrigger = SharpGL.RenderTrigger.TimerBased;
            this.sceneControl1.Size = new System.Drawing.Size(433, 405);
            this.sceneControl1.TabIndex = 0;
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.splitContainer2);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.panel3);
            this.splitContainer1.Panel2.Controls.Add(this.zoomScale);
            this.splitContainer1.Panel2.Controls.Add(this.trackBar1);
            this.splitContainer1.Panel2.Controls.Add(this.panel2);
            this.splitContainer1.Panel2.Controls.Add(this.panel1);
            this.splitContainer1.Panel2.Controls.Add(this.sceneControl1);
            this.splitContainer1.Size = new System.Drawing.Size(820, 460);
            this.splitContainer1.SplitterDistance = 157;
            this.splitContainer1.TabIndex = 6;
            // 
            // splitContainer2
            // 
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Name = "splitContainer2";
            this.splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.Controls.Add(this.treeView1);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.propertyGrid1);
            this.splitContainer2.Size = new System.Drawing.Size(157, 460);
            this.splitContainer2.SplitterDistance = 230;
            this.splitContainer2.TabIndex = 7;
            // 
            // treeView1
            // 
            this.treeView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.treeView1.Location = new System.Drawing.Point(0, 0);
            this.treeView1.Name = "treeView1";
            this.treeView1.Size = new System.Drawing.Size(157, 230);
            this.treeView1.TabIndex = 6;
            this.treeView1.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeView1_AfterSelect);
            // 
            // propertyGrid1
            // 
            this.propertyGrid1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.propertyGrid1.Location = new System.Drawing.Point(0, 0);
            this.propertyGrid1.Name = "propertyGrid1";
            this.propertyGrid1.Size = new System.Drawing.Size(157, 226);
            this.propertyGrid1.TabIndex = 0;
            // 
            // panel3
            // 
            this.panel3.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel3.Controls.Add(this.label7);
            this.panel3.Controls.Add(this.textBox4);
            this.panel3.Controls.Add(this.textBox1);
            this.panel3.Controls.Add(this.textBox2);
            this.panel3.Controls.Add(this.textBox3);
            this.panel3.Controls.Add(this.label6);
            this.panel3.Location = new System.Drawing.Point(457, 336);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(199, 120);
            this.panel3.TabIndex = 11;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(54, 12);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(102, 13);
            this.label7.TabIndex = 11;
            this.label7.Text = "Calculated Distance";
            // 
            // textBox4
            // 
            this.textBox4.Location = new System.Drawing.Point(75, 29);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(45, 20);
            this.textBox4.TabIndex = 10;
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(137, 78);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(45, 20);
            this.textBox1.TabIndex = 3;
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(75, 78);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(45, 20);
            this.textBox2.TabIndex = 2;
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(13, 78);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(45, 20);
            this.textBox3.TabIndex = 1;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(32, 52);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(141, 13);
            this.label6.TabIndex = 0;
            this.label6.Text = "Target 3D Point Coordinates";
            // 
            // zoomScale
            // 
            this.zoomScale.Location = new System.Drawing.Point(45, 411);
            this.zoomScale.Name = "zoomScale";
            this.zoomScale.Size = new System.Drawing.Size(354, 45);
            this.zoomScale.TabIndex = 10;
            this.zoomScale.ValueChanged += new System.EventHandler(this.ZoomChanged);
            // 
            // trackBar1
            // 
            this.trackBar1.Location = new System.Drawing.Point(124, 421);
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.Size = new System.Drawing.Size(104, 45);
            this.trackBar1.TabIndex = 9;
            // 
            // panel2
            // 
            this.panel2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel2.Controls.Add(this.updateBtn);
            this.panel2.Controls.Add(this.label5);
            this.panel2.Controls.Add(this.baseRadius);
            this.panel2.Controls.Add(this.label2);
            this.panel2.Controls.Add(this.topPosZ);
            this.panel2.Controls.Add(this.topPosY);
            this.panel2.Controls.Add(this.topPosX);
            this.panel2.Controls.Add(this.label3);
            this.panel2.Controls.Add(this.bottomPosZ);
            this.panel2.Controls.Add(this.bottomPosY);
            this.panel2.Controls.Add(this.bottomPosX);
            this.panel2.Controls.Add(this.label4);
            this.panel2.Location = new System.Drawing.Point(457, 94);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(199, 221);
            this.panel2.TabIndex = 8;
            // 
            // updateBtn
            // 
            this.updateBtn.Location = new System.Drawing.Point(3, 193);
            this.updateBtn.Name = "updateBtn";
            this.updateBtn.Size = new System.Drawing.Size(56, 23);
            this.updateBtn.TabIndex = 11;
            this.updateBtn.Text = "update";
            this.updateBtn.UseVisualStyleBackColor = true;
            this.updateBtn.Click += new System.EventHandler(this.RedrawCylinder);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(62, 150);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(67, 13);
            this.label5.TabIndex = 10;
            this.label5.Text = "Base Radius";
            // 
            // baseRadius
            // 
            this.baseRadius.Location = new System.Drawing.Point(75, 171);
            this.baseRadius.Name = "baseRadius";
            this.baseRadius.Size = new System.Drawing.Size(45, 20);
            this.baseRadius.TabIndex = 9;
            this.baseRadius.TextChanged += new System.EventHandler(this.UpdateRadius);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(35, 36);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(126, 13);
            this.label2.TabIndex = 8;
            this.label2.Text = "Bottom Point Coordinates";
            // 
            // topPosZ
            // 
            this.topPosZ.Location = new System.Drawing.Point(137, 119);
            this.topPosZ.Name = "topPosZ";
            this.topPosZ.Size = new System.Drawing.Size(45, 20);
            this.topPosZ.TabIndex = 7;
            // 
            // topPosY
            // 
            this.topPosY.Location = new System.Drawing.Point(75, 119);
            this.topPosY.Name = "topPosY";
            this.topPosY.Size = new System.Drawing.Size(45, 20);
            this.topPosY.TabIndex = 6;
            // 
            // topPosX
            // 
            this.topPosX.Location = new System.Drawing.Point(13, 119);
            this.topPosX.Name = "topPosX";
            this.topPosX.Size = new System.Drawing.Size(45, 20);
            this.topPosX.TabIndex = 5;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(42, 93);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(112, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Top Point Coordinates";
            // 
            // bottomPosZ
            // 
            this.bottomPosZ.Location = new System.Drawing.Point(137, 64);
            this.bottomPosZ.Name = "bottomPosZ";
            this.bottomPosZ.Size = new System.Drawing.Size(45, 20);
            this.bottomPosZ.TabIndex = 3;
            // 
            // bottomPosY
            // 
            this.bottomPosY.Location = new System.Drawing.Point(75, 64);
            this.bottomPosY.Name = "bottomPosY";
            this.bottomPosY.Size = new System.Drawing.Size(45, 20);
            this.bottomPosY.TabIndex = 2;
            // 
            // bottomPosX
            // 
            this.bottomPosX.Location = new System.Drawing.Point(13, 64);
            this.bottomPosX.Name = "bottomPosX";
            this.bottomPosX.Size = new System.Drawing.Size(45, 20);
            this.bottomPosX.TabIndex = 1;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(48, 11);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(100, 13);
            this.label4.TabIndex = 0;
            this.label4.Text = "Cylinder Parameters";
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.ptPosZ);
            this.panel1.Controls.Add(this.ptPosY);
            this.panel1.Controls.Add(this.ptPosX);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Location = new System.Drawing.Point(457, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(199, 88);
            this.panel1.TabIndex = 7;
            // 
            // ptPosZ
            // 
            this.ptPosZ.Location = new System.Drawing.Point(137, 49);
            this.ptPosZ.Name = "ptPosZ";
            this.ptPosZ.Size = new System.Drawing.Size(45, 20);
            this.ptPosZ.TabIndex = 3;
            // 
            // ptPosY
            // 
            this.ptPosY.Location = new System.Drawing.Point(75, 49);
            this.ptPosY.Name = "ptPosY";
            this.ptPosY.Size = new System.Drawing.Size(45, 20);
            this.ptPosY.TabIndex = 2;
            // 
            // ptPosX
            // 
            this.ptPosX.Location = new System.Drawing.Point(13, 49);
            this.ptPosX.Name = "ptPosX";
            this.ptPosX.Size = new System.Drawing.Size(45, 20);
            this.ptPosX.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(32, 19);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(144, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Source 3D Point Coordinates";
            // 
            // FormSceneSample
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(820, 460);
            this.Controls.Add(this.splitContainer1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "FormSceneSample";
            this.Text = "Scene Sample";
            ((System.ComponentModel.ISupportInitialize)(this.sceneControl1)).EndInit();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
            this.splitContainer2.ResumeLayout(false);
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.zoomScale)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private SharpGL.SceneControl sceneControl1;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.TreeView treeView1;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.PropertyGrid propertyGrid1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.TextBox ptPosZ;
        private System.Windows.Forms.TextBox ptPosY;
        private System.Windows.Forms.TextBox ptPosX;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox baseRadius;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox topPosZ;
        private System.Windows.Forms.TextBox topPosY;
        private System.Windows.Forms.TextBox topPosX;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox bottomPosZ;
        private System.Windows.Forms.TextBox bottomPosY;
        private System.Windows.Forms.TextBox bottomPosX;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TrackBar zoomScale;
        private System.Windows.Forms.TrackBar trackBar1;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button updateBtn;
    }
}

