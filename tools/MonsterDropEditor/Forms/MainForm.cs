using System.ComponentModel;
using MonsterDropEditor.Core;
using MonsterDropEditor.Models;

namespace MonsterDropEditor.Forms
{
    public partial class MainForm : Form
    {
        private MemoryManager memoryManager;
        private List<MobEntry> mobEntries;
        private BindingSource mobBindingSource;
        private BindingSource dropBindingSource;
        private MobEntry? selectedMob;
        private bool isUpdating = false;

        // UI Controls
        private MenuStrip menuStrip;
        private ToolStrip toolStrip;
        private SplitContainer mainSplitContainer;
        private GroupBox processGroupBox;
        private ComboBox processComboBox;
        private Button attachButton;
        private Button scanButton;
        private Label statusLabel;
        
        private GroupBox mobListGroupBox;
        private DataGridView mobDataGridView;
        private TextBox searchTextBox;
        private Button searchButton;
        
        private GroupBox dropEditGroupBox;
        private Label selectedMobLabel;
        private DataGridView dropDataGridView;
        private GroupBox massEditGroupBox;
        private NumericUpDown fromGradeNumeric;
        private NumericUpDown toGradeNumeric;
        private NumericUpDown newRateNumeric;
        private Button applyMassEditButton;
        private Button resetDropsButton;
        private Button saveChangesButton;

        public MainForm()
        {
            memoryManager = new MemoryManager();
            mobEntries = new List<MobEntry>();
            mobBindingSource = new BindingSource();
            dropBindingSource = new BindingSource();
            
            InitializeComponent();
            SetupDataBindings();
            RefreshProcessList();
        }

        private void InitializeComponent()
        {
            this.Text = "Shaiya Monster Drop Editor v1.0";
            this.Size = new Size(1200, 800);
            this.StartPosition = FormStartPosition.CenterScreen;
            this.MinimumSize = new Size(800, 600);

            // Create menu strip
            CreateMenuStrip();
            
            // Create tool strip
            CreateToolStrip();
            
            // Main split container
            mainSplitContainer = new SplitContainer()
            {
                Dock = DockStyle.Fill,
                Orientation = Orientation.Horizontal,
                SplitterDistance = 300,
                FixedPanel = FixedPanel.Panel1
            };
            
            CreateTopPanel();
            CreateBottomPanel();
            
            this.Controls.Add(mainSplitContainer);
            this.Controls.Add(toolStrip);
            this.Controls.Add(menuStrip);
            
            // Status bar
            statusLabel = new Label()
            {
                Text = "Ready - Please attach to Shaiya process",
                Dock = DockStyle.Bottom,
                BackColor = Color.LightGray,
                Padding = new Padding(5)
            };
            this.Controls.Add(statusLabel);
        }

        private void CreateMenuStrip()
        {
            menuStrip = new MenuStrip();
            
            // File menu
            var fileMenu = new ToolStripMenuItem("&File");
            fileMenu.DropDownItems.Add("&Export Drop Data...", null, ExportDropData_Click);
            fileMenu.DropDownItems.Add("&Import Drop Data...", null, ImportDropData_Click);
            fileMenu.DropDownItems.Add(new ToolStripSeparator());
            fileMenu.DropDownItems.Add("E&xit", null, (s, e) => this.Close());
            
            // Tools menu
            var toolsMenu = new ToolStripMenuItem("&Tools");
            toolsMenu.DropDownItems.Add("&Refresh Process List", null, RefreshProcessList_Click);
            toolsMenu.DropDownItems.Add("&Scan for Mobs", null, ScanMobs_Click);
            toolsMenu.DropDownItems.Add(new ToolStripSeparator());
            toolsMenu.DropDownItems.Add("&Mass Edit All Drops...", null, MassEditAll_Click);
            
            // Help menu
            var helpMenu = new ToolStripMenuItem("&Help");
            helpMenu.DropDownItems.Add("&About", null, About_Click);
            
            menuStrip.Items.AddRange(new ToolStripItem[] { fileMenu, toolsMenu, helpMenu });
        }

        private void CreateToolStrip()
        {
            toolStrip = new ToolStrip();
            
            var attachToolStripButton = new ToolStripButton("Attach", null, AttachProcess_Click)
            {
                DisplayStyle = ToolStripItemDisplayStyle.ImageAndText
            };
            
            var scanToolStripButton = new ToolStripButton("Scan Mobs", null, ScanMobs_Click)
            {
                DisplayStyle = ToolStripItemDisplayStyle.ImageAndText
            };
            
            var saveToolStripButton = new ToolStripButton("Save Changes", null, SaveChanges_Click)
            {
                DisplayStyle = ToolStripItemDisplayStyle.ImageAndText
            };
            
            toolStrip.Items.AddRange(new ToolStripItem[] 
            { 
                attachToolStripButton, 
                new ToolStripSeparator(),
                scanToolStripButton,
                new ToolStripSeparator(),
                saveToolStripButton
            });
        }

        private void CreateTopPanel()
        {
            var topPanel = new Panel() { Dock = DockStyle.Fill };
            
            // Process connection group
            processGroupBox = new GroupBox()
            {
                Text = "Process Connection",
                Dock = DockStyle.Top,
                Height = 80
            };
            
            processComboBox = new ComboBox()
            {
                Location = new Point(10, 25),
                Size = new Size(300, 23),
                DropDownStyle = ComboBoxStyle.DropDownList
            };
            
            attachButton = new Button()
            {
                Text = "Attach",
                Location = new Point(320, 24),
                Size = new Size(80, 25)
            };
            attachButton.Click += AttachProcess_Click;
            
            scanButton = new Button()
            {
                Text = "Scan Mobs",
                Location = new Point(410, 24),
                Size = new Size(80, 25),
                Enabled = false
            };
            scanButton.Click += ScanMobs_Click;
            
            processGroupBox.Controls.AddRange(new Control[] { processComboBox, attachButton, scanButton });
            
            // Mob list group
            mobListGroupBox = new GroupBox()
            {
                Text = "Monster List",
                Dock = DockStyle.Fill
            };
            
            searchTextBox = new TextBox()
            {
                Location = new Point(10, 25),
                Size = new Size(200, 23),
                PlaceholderText = "Search by name or ID..."
            };
            
            searchButton = new Button()
            {
                Text = "Search",
                Location = new Point(220, 24),
                Size = new Size(60, 25)
            };
            searchButton.Click += SearchMobs_Click;
            
            mobDataGridView = new DataGridView()
            {
                Location = new Point(10, 55),
                Size = new Size(mobListGroupBox.Width - 20, mobListGroupBox.Height - 70),
                Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right,
                AutoGenerateColumns = false,
                SelectionMode = DataGridViewSelectionMode.FullRowSelect,
                MultiSelect = false,
                ReadOnly = true,
                AllowUserToAddRows = false,
                AllowUserToDeleteRows = false
            };
            
            // Setup mob grid columns
            mobDataGridView.Columns.Add(new DataGridViewTextBoxColumn() 
            { 
                DataPropertyName = "Info.MobId", 
                HeaderText = "ID", 
                Width = 60 
            });
            mobDataGridView.Columns.Add(new DataGridViewTextBoxColumn() 
            { 
                DataPropertyName = "DisplayName", 
                HeaderText = "Name", 
                Width = 200 
            });
            mobDataGridView.Columns.Add(new DataGridViewTextBoxColumn() 
            { 
                DataPropertyName = "Info.Level", 
                HeaderText = "Level", 
                Width = 60 
            });
            mobDataGridView.Columns.Add(new DataGridViewCheckBoxColumn() 
            { 
                DataPropertyName = "IsModified", 
                HeaderText = "Modified", 
                Width = 70 
            });
            
            mobDataGridView.SelectionChanged += MobDataGridView_SelectionChanged;
            
            mobListGroupBox.Controls.AddRange(new Control[] { searchTextBox, searchButton, mobDataGridView });
            
            topPanel.Controls.Add(mobListGroupBox);
            topPanel.Controls.Add(processGroupBox);
            
            mainSplitContainer.Panel1.Controls.Add(topPanel);
        }

        private void CreateBottomPanel()
        {
            var bottomPanel = new Panel() { Dock = DockStyle.Fill };
            
            var bottomSplitContainer = new SplitContainer()
            {
                Dock = DockStyle.Fill,
                Orientation = Orientation.Vertical,
                SplitterDistance = 400
            };
            
            // Drop edit group (left side)
            dropEditGroupBox = new GroupBox()
            {
                Text = "Drop Editor",
                Dock = DockStyle.Fill
            };
            
            selectedMobLabel = new Label()
            {
                Text = "No mob selected",
                Location = new Point(10, 25),
                Size = new Size(380, 23),
                Font = new Font(Font, FontStyle.Bold)
            };
            
            dropDataGridView = new DataGridView()
            {
                Location = new Point(10, 55),
                Size = new Size(380, 300),
                Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right,
                AutoGenerateColumns = false,
                SelectionMode = DataGridViewSelectionMode.CellSelect,
                AllowUserToAddRows = false,
                AllowUserToDeleteRows = false
            };
            
            // Setup drop grid columns
            dropDataGridView.Columns.Add(new DataGridViewTextBoxColumn() 
            { 
                DataPropertyName = "Grade", 
                HeaderText = "Grade", 
                Width = 80 
            });
            dropDataGridView.Columns.Add(new DataGridViewTextBoxColumn() 
            { 
                DataPropertyName = "Rate", 
                HeaderText = "Rate", 
                Width = 100 
            });
            
            dropDataGridView.CellValueChanged += DropDataGridView_CellValueChanged;
            
            resetDropsButton = new Button()
            {
                Text = "Reset Drops",
                Size = new Size(100, 25),
                Anchor = AnchorStyles.Bottom | AnchorStyles.Left
            };
            resetDropsButton.Location = new Point(10, dropEditGroupBox.Height - 35);
            resetDropsButton.Click += ResetDrops_Click;
            
            dropEditGroupBox.Controls.AddRange(new Control[] { selectedMobLabel, dropDataGridView, resetDropsButton });
            
            // Mass edit group (right side)
            massEditGroupBox = new GroupBox()
            {
                Text = "Mass Edit",
                Dock = DockStyle.Fill
            };
            
            var gradeLabel = new Label()
            {
                Text = "Grade Range:",
                Location = new Point(10, 30),
                Size = new Size(80, 23)
            };
            
            fromGradeNumeric = new NumericUpDown()
            {
                Location = new Point(100, 28),
                Size = new Size(60, 23),
                Minimum = 0,
                Maximum = 65535,
                Value = 0
            };
            
            var toLabel = new Label()
            {
                Text = "to",
                Location = new Point(170, 30),
                Size = new Size(20, 23)
            };
            
            toGradeNumeric = new NumericUpDown()
            {
                Location = new Point(200, 28),
                Size = new Size(60, 23),
                Minimum = 0,
                Maximum = 65535,
                Value = 65535
            };
            
            var newRateLabel = new Label()
            {
                Text = "New Rate:",
                Location = new Point(10, 65),
                Size = new Size(80, 23)
            };
            
            newRateNumeric = new NumericUpDown()
            {
                Location = new Point(100, 63),
                Size = new Size(100, 23),
                Minimum = 0,
                Maximum = uint.MaxValue,
                Value = 1000
            };
            
            applyMassEditButton = new Button()
            {
                Text = "Apply to Selected",
                Location = new Point(10, 100),
                Size = new Size(120, 25),
                Enabled = false
            };
            applyMassEditButton.Click += ApplyMassEdit_Click;
            
            saveChangesButton = new Button()
            {
                Text = "Save All Changes",
                Location = new Point(10, 135),
                Size = new Size(120, 25),
                BackColor = Color.LightGreen,
                Enabled = false
            };
            saveChangesButton.Click += SaveChanges_Click;
            
            massEditGroupBox.Controls.AddRange(new Control[] 
            { 
                gradeLabel, fromGradeNumeric, toLabel, toGradeNumeric,
                newRateLabel, newRateNumeric, applyMassEditButton, saveChangesButton
            });
            
            bottomSplitContainer.Panel1.Controls.Add(dropEditGroupBox);
            bottomSplitContainer.Panel2.Controls.Add(massEditGroupBox);
            
            bottomPanel.Controls.Add(bottomSplitContainer);
            mainSplitContainer.Panel2.Controls.Add(bottomPanel);
        }

        private void SetupDataBindings()
        {
            mobBindingSource.DataSource = mobEntries;
            mobDataGridView.DataSource = mobBindingSource;
            
            dropDataGridView.DataSource = dropBindingSource;
        }

        // Event Handlers
        private void RefreshProcessList_Click(object? sender, EventArgs e)
        {
            RefreshProcessList();
        }

        private void RefreshProcessList()
        {
            processComboBox.Items.Clear();
            var processes = memoryManager.GetShaiyaProcesses();
            
            foreach (var (name, id) in processes)
            {
                processComboBox.Items.Add($"{name} (PID: {id})");
            }
            
            if (processComboBox.Items.Count > 0)
            {
                processComboBox.SelectedIndex = 0;
            }
            
            statusLabel.Text = $"Found {processComboBox.Items.Count} Shaiya process(es)";
        }

        private void AttachProcess_Click(object? sender, EventArgs e)
        {
            if (processComboBox.SelectedItem == null)
            {
                MessageBox.Show("Please select a process first.", "No Process Selected", 
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            
            string selectedText = processComboBox.SelectedItem.ToString()!;
            string processName = selectedText.Substring(0, selectedText.IndexOf(" (PID:"));
            
            if (memoryManager.AttachToProcess(processName))
            {
                attachButton.Text = "Detach";
                scanButton.Enabled = true;
                statusLabel.Text = $"Attached to {processName} - Ready to scan for mobs";
                statusLabel.BackColor = Color.LightGreen;
            }
            else
            {
                MessageBox.Show($"Failed to attach to {processName}. Make sure the process is running and you have sufficient privileges.", 
                    "Attach Failed", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void ScanMobs_Click(object? sender, EventArgs e)
        {
            if (!memoryManager.IsAttached)
            {
                MessageBox.Show("Please attach to a process first.", "Not Attached", 
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            
            statusLabel.Text = "Scanning for mobs... This may take a moment.";
            statusLabel.BackColor = Color.Yellow;
            Application.DoEvents();
            
            var mobs = memoryManager.ScanForMobs();
            
            mobEntries.Clear();
            mobEntries.AddRange(mobs);
            mobBindingSource.ResetBindings(false);
            
            statusLabel.Text = $"Found {mobs.Count} mobs in memory";
            statusLabel.BackColor = Color.LightGreen;
        }

        private void SearchMobs_Click(object? sender, EventArgs e)
        {
            string searchTerm = searchTextBox.Text.Trim().ToLower();
            if (string.IsNullOrEmpty(searchTerm))
            {
                mobBindingSource.DataSource = mobEntries;
                return;
            }
            
            var filtered = mobEntries.Where(m => 
                m.Info.MobId.ToString().Contains(searchTerm) ||
                m.Info.GetMobName().ToLower().Contains(searchTerm) ||
                m.Info.Level.ToString().Contains(searchTerm)
            ).ToList();
            
            mobBindingSource.DataSource = filtered;
        }

        private void MobDataGridView_SelectionChanged(object? sender, EventArgs e)
        {
            if (isUpdating) return;
            
            if (mobDataGridView.SelectedRows.Count > 0)
            {
                selectedMob = (MobEntry)mobDataGridView.SelectedRows[0].DataBoundItem;
                LoadSelectedMobDrops();
                applyMassEditButton.Enabled = true;
            }
            else
            {
                selectedMob = null;
                dropBindingSource.DataSource = null;
                selectedMobLabel.Text = "No mob selected";
                applyMassEditButton.Enabled = false;
            }
        }

        private void LoadSelectedMobDrops()
        {
            if (selectedMob == null) return;
            
            selectedMobLabel.Text = selectedMob.DisplayName;
            
            var dropList = selectedMob.Info.DropInfo?.ToList() ?? new List<MobItemDropInfo>();
            dropBindingSource.DataSource = dropList;
        }

        private void DropDataGridView_CellValueChanged(object? sender, DataGridViewCellValueChangedEventArgs e)
        {
            if (selectedMob == null || isUpdating) return;
            
            // Mark mob as modified
            selectedMob.IsModified = true;
            saveChangesButton.Enabled = true;
            
            // Update the mob entry with new values
            var dropList = (List<MobItemDropInfo>)dropBindingSource.DataSource;
            selectedMob.Info.DropInfo = dropList.ToArray();
            
            // Refresh the mob list to show modified status
            mobBindingSource.ResetBindings(false);
        }

        private void ApplyMassEdit_Click(object? sender, EventArgs e)
        {
            if (selectedMob == null) return;
            
            ushort fromGrade = (ushort)fromGradeNumeric.Value;
            ushort toGrade = (ushort)toGradeNumeric.Value;
            uint newRate = (uint)newRateNumeric.Value;
            
            if (fromGrade > toGrade)
            {
                MessageBox.Show("From grade cannot be greater than to grade.", "Invalid Range", 
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            
            isUpdating = true;
            
            for (int i = 0; i < selectedMob.Info.DropInfo.Length; i++)
            {
                if (selectedMob.Info.DropInfo[i].Grade >= fromGrade && 
                    selectedMob.Info.DropInfo[i].Grade <= toGrade)
                {
                    selectedMob.Info.DropInfo[i].Rate = newRate;
                }
            }
            
            selectedMob.IsModified = true;
            saveChangesButton.Enabled = true;
            
            LoadSelectedMobDrops();
            mobBindingSource.ResetBindings(false);
            
            isUpdating = false;
        }

        private void ResetDrops_Click(object? sender, EventArgs e)
        {
            if (selectedMob == null) return;
            
            var result = MessageBox.Show("Reset all drop rates for this mob to original values?", 
                "Confirm Reset", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            
            if (result == DialogResult.Yes)
            {
                Array.Copy(selectedMob.OriginalDropInfo, selectedMob.Info.DropInfo, 10);
                selectedMob.IsModified = false;
                
                LoadSelectedMobDrops();
                mobBindingSource.ResetBindings(false);
                
                // Check if any mobs are still modified
                saveChangesButton.Enabled = mobEntries.Any(m => m.IsModified);
            }
        }

        private void SaveChanges_Click(object? sender, EventArgs e)
        {
            if (!memoryManager.IsAttached)
            {
                MessageBox.Show("Not attached to process.", "Cannot Save", 
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            
            var modifiedMobs = mobEntries.Where(m => m.IsModified).ToList();
            
            if (modifiedMobs.Count == 0)
            {
                MessageBox.Show("No changes to save.", "No Changes", 
                    MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
            
            var result = MessageBox.Show($"Save changes to {modifiedMobs.Count} mob(s)?", 
                "Confirm Save", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            
            if (result == DialogResult.Yes)
            {
                int saved = 0;
                
                foreach (var mob in modifiedMobs)
                {
                    // Calculate offset to dropInfo in the MobInfo structure (0xBC)
                    IntPtr dropInfoAddress = new IntPtr(mob.Address.ToInt64() + 0xBC);
                    
                    // Convert drop info to byte array
                    byte[] dropData = new byte[10 * 8]; // 10 drops * 8 bytes each
                    
                    for (int i = 0; i < 10; i++)
                    {
                        byte[] gradeBytes = BitConverter.GetBytes(mob.Info.DropInfo[i].Grade);
                        byte[] rateBytes = BitConverter.GetBytes(mob.Info.DropInfo[i].Rate);
                        
                        Array.Copy(gradeBytes, 0, dropData, i * 8, 2);
                        // Skip 2 bytes padding
                        Array.Copy(rateBytes, 0, dropData, i * 8 + 4, 4);
                    }
                    
                    if (memoryManager.WriteMemory(dropInfoAddress, dropData))
                    {
                        saved++;
                    }
                }
                
                MessageBox.Show($"Saved {saved} of {modifiedMobs.Count} mob changes to memory.", 
                    "Save Complete", MessageBoxButtons.OK, MessageBoxIcon.Information);
                
                // Reset modified flags for successfully saved mobs
                foreach (var mob in modifiedMobs.Take(saved))
                {
                    mob.IsModified = false;
                }
                
                saveChangesButton.Enabled = mobEntries.Any(m => m.IsModified);
                mobBindingSource.ResetBindings(false);
            }
        }

        private void ExportDropData_Click(object? sender, EventArgs e)
        {
            // TODO: Implement export functionality
            MessageBox.Show("Export functionality not implemented yet.", "Not Implemented", 
                MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void ImportDropData_Click(object? sender, EventArgs e)
        {
            // TODO: Implement import functionality
            MessageBox.Show("Import functionality not implemented yet.", "Not Implemented", 
                MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void MassEditAll_Click(object? sender, EventArgs e)
        {
            // TODO: Implement mass edit all functionality
            MessageBox.Show("Mass edit all functionality not implemented yet.", "Not Implemented", 
                MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void About_Click(object? sender, EventArgs e)
        {
            MessageBox.Show($"Shaiya Monster Drop Editor v1.0\n\n" +
                          $"A tool for editing monster drop rates in Shaiya Episode 6\n" +
                          $"Built for the Shaiya community\n\n" +
                          $"© 2025", 
                          "About", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        protected override void OnFormClosed(FormClosedEventArgs e)
        {
            memoryManager?.Dispose();
            base.OnFormClosed(e);
        }
    }
}