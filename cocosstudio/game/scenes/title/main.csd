<GameFile>
  <PropertyGroup Name="main" Type="Scene" ID="5007cd57-1a5e-46f2-af9e-04784aa1e44b" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="30" Speed="1.0000" ActivedAnimationName="main">
        <Timeline ActionTag="1490584752" Property="Position">
          <PointFrame FrameIndex="0" X="426.0000" Y="240.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="15" X="426.0000" Y="240.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="30" X="426.0000" Y="240.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1490584752" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="1.2500" Y="1.2500">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1490584752" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="main" StartIndex="0" EndIndex="120">
          <RenderColor A="255" R="255" G="255" B="0" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Scene" Tag="46" ctype="GameNodeObjectData">
        <Size X="852.0000" Y="480.0000" />
        <Children>
          <AbstractNodeData Name="audio" ActionTag="-882439077" Tag="91" IconVisible="True" LeftMargin="-130.6699" RightMargin="982.6699" TopMargin="733.1729" BottomMargin="-253.1729" Volume="1.0000" Loop="True" ctype="SimpleAudioObjectData">
            <Size X="0.0000" Y="0.0000" />
            <AnchorPoint />
            <Position X="-130.6699" Y="-253.1729" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="-0.1534" Y="-0.5274" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="content/sounds/bgm/title/title_sound.mp3" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="gyng" ActionTag="1490584752" Tag="133" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="365.0000" RightMargin="365.0000" TopMargin="170.0000" BottomMargin="170.0000" ctype="SpriteObjectData">
            <Size X="122.0000" Y="140.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="426.0000" Y="240.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="0.1432" Y="0.2917" />
            <FileData Type="Normal" Path="content/animations/title/gyng_ld.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="start" ActionTag="418439078" Tag="38" IconVisible="True" LeftMargin="51.9229" RightMargin="800.0771" TopMargin="733.1210" BottomMargin="-253.1210" Volume="1.0000" ctype="SimpleAudioObjectData">
            <Size X="0.0000" Y="0.0000" />
            <AnchorPoint />
            <Position X="51.9229" Y="-253.1210" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0609" Y="-0.5273" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="content/sounds/sfx/title/start_sound.mp3" Plist="" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>