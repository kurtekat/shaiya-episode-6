USE [PS_GameDefs]
GO

/****** Object:  Table [dbo].[Items]    Script Date: 5/4/2024 3:45:34 AM ******/
DROP TABLE [dbo].[Items]
GO

/****** Object:  Table [dbo].[Items]    Script Date: 5/4/2024 3:45:34 AM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[Items](
	[RowID] [int] IDENTITY(1,1) NOT NULL,
	[ItemID] [int] NOT NULL,
	[ItemName] [varchar](30) NOT NULL,
	[Type] [tinyint] NOT NULL,
	[TypeID] [tinyint] NOT NULL,
	[Reqlevel] [smallint] NOT NULL,
	[Country] [tinyint] NOT NULL,
	[Attackfighter] [tinyint] NOT NULL,
	[Defensefighter] [tinyint] NOT NULL,
	[Patrolrogue] [tinyint] NOT NULL,
	[Shootrogue] [tinyint] NOT NULL,
	[Attackmage] [tinyint] NOT NULL,
	[Defensemage] [tinyint] NOT NULL,
	[Grow] [tinyint] NOT NULL,
	[ReqStr] [smallint] NOT NULL,
	[ReqDex] [smallint] NOT NULL,
	[ReqRec] [smallint] NOT NULL,
	[ReqInt] [smallint] NOT NULL,
	[ReqWis] [smallint] NOT NULL,
	[Reqluc] [smallint] NOT NULL,
	[ReqVg] [smallint] NOT NULL,
	[ReqOg] [tinyint] NOT NULL,
	[ReqIg] [tinyint] NOT NULL,
	[Range] [smallint] NOT NULL,
	[AttackTime] [tinyint] NOT NULL,
	[Attrib] [tinyint] NOT NULL,
	[Special] [tinyint] NOT NULL,
	[Slot] [tinyint] NOT NULL,
	[Quality] [smallint] NOT NULL,
	[Effect1] [smallint] NOT NULL,
	[Effect2] [smallint] NOT NULL,
	[Effect3] [smallint] NOT NULL,
	[Effect4] [smallint] NOT NULL,
	[ConstHP] [smallint] NOT NULL,
	[ConstSP] [smallint] NOT NULL,
	[ConstMP] [smallint] NOT NULL,
	[ConstStr] [smallint] NOT NULL,
	[ConstDex] [smallint] NOT NULL,
	[ConstRec] [smallint] NOT NULL,
	[ConstInt] [smallint] NOT NULL,
	[ConstWis] [smallint] NOT NULL,
	[ConstLuc] [smallint] NOT NULL,
	[Speed] [tinyint] NOT NULL,
	[Exp] [tinyint] NOT NULL,
	[Buy] [int] NOT NULL,
	[Sell] [int] NOT NULL,
	[Grade] [smallint] NOT NULL,
	[Drop] [smallint] NOT NULL,
	[Server] [tinyint] NOT NULL,
	[Count] [tinyint] NOT NULL,
    [Duration] [int] NOT NULL
 CONSTRAINT [PK_Items] PRIMARY KEY NONCLUSTERED 
(
	[ItemID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO


