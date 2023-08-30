USE [PS_GameData]
GO
/****** Object:  StoredProcedure [dbo].[usp_Save_Char_Info_E]    Script Date: 19/07/2015 21:38:39 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

ALTER Proc [dbo].[usp_Save_Char_Info_E]

@CharID int,
@Level int,
@StatPoint smallint,
@SkillPoint smallint,
@Str smallint,
@Dex smallint,
@Rec smallint,
@Int smallint,
@Wis smallint,
@Luc smallint,
@Hp smallint,
@Mp smallint,
@Sp smallint,
@Map smallint,
@Dir smallint,
@Exp int,
@Money int,
@Posx varchar(50),
@Posy varchar(50),
@Posz varchar(50),
@Hg int,
@Vg int,
@Cg int,
@Og int,
@Ig int,
@K1 int = null,
@K2 int = null,
@K3 int = null,
@K4 int = null,
@KillLevel tinyint,
@DeadLevel tinyint

AS

SET NOCOUNT ON

DECLARE @ServerID int,
        @Grow     int,
        @tempExp  bigint,
        @PosxR    real,
        @PosyR    real,
        @PoszR    real

SET @ServerID = 1

IF (ISNumeric(@Posx) = 1 and ISNumeric(@Posy) = 1 and ISNumeric(@Posz) = 1)
BEGIN
    SET @PosxR = CAST(@Posx as real)
    SET @PosyR = CAST(@Posy as real)
    SET @PoszR = CAST(@Posz as real)
END
ELSE
BEGIN
    --Only gets here if there is a error in the positions, Most likely a bot or exploit.
    --Log in a error table for manual invest.
    --Set all the pos. to bootleg so it doesn't throw an error
    SET @Map = 42
    SET @PosxR = 66.5
    SET @PosYR = 2.0
    SET @PosZR = 52.6
END

UPDATE Chars
    SET [Level] = @Level, StatPoint = @StatPoint, SkillPoint = @SkillPoint,
    [Str] = @Str, dex = @Dex, Rec = @Rec, [int] = @Int, Wis = @Wis, Luc = @Luc,
    HP = @Hp, Mp = @Mp, Sp = @Sp,
    Map = @Map, dir = @Dir, [exp] = @Exp, [money] = @Money,
    PosX = @PosxR, PosY = @PosYR, PosZ = @PosZR, hg = @Hg, vg = @Vg, cg = @Cg, og = @Og, ig = @Ig, 
    KillLevel=@KillLevel, DeadLevel=@DeadLevel,LeaveDate=GETDATE()
WHERE CharID = @CharID

IF( (@K1 IS NOT NULL) AND (@K2 IS NOT NULL) AND (@K3 IS NOT NULL) AND (@K4 IS NOT NULL))
BEGIN
    UPDATE Chars SET K1=@K1, K2=@K2, K3=@K3, K4=@K4 WHERE CharID=@CharID
END

IF(@@ERROR = 0 AND @@ROWCOUNT = 1)
BEGIN
    RETURN 1
END
ELSE
BEGIN
    RETURN -1
END

SET NOCOUNT OFF
