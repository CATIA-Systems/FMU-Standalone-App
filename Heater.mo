within ;
model Heater
  Modelica.Electrical.Analog.Basic.Ground ground
                              annotation (Placement(transformation(extent={{-90,-92},
            {-70,-72}})));
  Modelica.Electrical.Analog.Sources.ConstantVoltage constantVoltage(V=10)
                                                        annotation (Placement(
        transformation(
        origin={-80,-40},
        extent={{-10,-10},{10,10}},
        rotation=270)));
  Modelica.Thermal.HeatTransfer.Components.HeatCapacitor
                                        heatCapacitor(C=1, T(start=TAmb, fixed=
          true))
    annotation (Placement(transformation(extent={{10,-52},{30,-72}})));
  Modelica.Electrical.Analog.Basic.HeatingResistor heatingResistor(
    R_ref=10,
    T_ref=293.15,
    alpha=1/255) annotation (Placement(transformation(
        origin={-20,-40},
        extent={{-10,10},{10,-10}},
        rotation=270)));
  Modelica.Thermal.HeatTransfer.Sources.FixedTemperature
                                        fixedTemperature(T=TAmb)
    annotation (Placement(transformation(extent={{90,-50},{70,-30}})));
  Modelica.Thermal.HeatTransfer.Celsius.TemperatureSensor
                                         temperatureSensor annotation (Placement(
        transformation(
        origin={50,0},
        extent={{-10,-10},{10,10}},
        rotation=0)));
  Modelica.Thermal.HeatTransfer.Components.ThermalConductor
                                           thermalConductor(G=0.1)
                                                        annotation (Placement(
        transformation(extent={{40,-50},{60,-30}})));
  Modelica.Electrical.Analog.Ideal.IdealOpeningSwitch idealSwitch
        annotation (Placement(transformation(extent={{-60,-30},{-40,-10}})));
  Modelica.Blocks.Interfaces.RealOutput T
    "Absolute temperature in degree Celsius as output signal"
    annotation (Placement(transformation(extent={{100,-10},{120,10}})));
  Modelica.Blocks.Interfaces.BooleanInput u
    "true => switch open, false => p--n connected"
    annotation (Placement(transformation(extent={{-140,-20},{-100,20}})));
equation
  connect(constantVoltage.n,heatingResistor. n) annotation (Line(points={{-80,-50},
          {-80,-60},{-20,-60},{-20,-50}},
                      color={0,0,255}));
  connect(constantVoltage.n,ground. p) annotation (Line(points={{-80,-50},{-80,
          -72}},      color={0,0,255}));
  connect(heatingResistor.heatPort,thermalConductor. port_a) annotation (Line(
        points={{-10,-40},{40,-40}}, color={191,0,0}));
  connect(thermalConductor.port_b,fixedTemperature. port) annotation (Line(
        points={{60,-40},{70,-40}}, color={191,0,0}));
  connect(heatingResistor.heatPort,temperatureSensor. port) annotation (Line(
        points={{-10,-40},{20,-40},{20,0},{40,0}},
                                              color={191,0,0}));
  connect(heatingResistor.heatPort,heatCapacitor. port) annotation (Line(
        points={{-10,-40},{20,-40},{20,-52}}, color={191,0,0}));
  connect(constantVoltage.p,idealSwitch. p) annotation (Line(points={{-80,-30},
          {-80,-20},{-60,-20}},
                           color={0,0,255}));
  connect(idealSwitch.n,heatingResistor. p) annotation (Line(points={{-40,-20},
          {-20,-20},{-20,-30}},
                      color={0,0,255}));
  connect(temperatureSensor.T, T)
    annotation (Line(points={{60,0},{110,0}}, color={0,0,127}));
  connect(idealSwitch.control, u)
    annotation (Line(points={{-50,-8},{-50,0},{-120,0}}, color={255,0,255}));
  annotation (
    Icon(coordinateSystem(preserveAspectRatio=false)),
    Diagram(coordinateSystem(preserveAspectRatio=false)),
    uses(Modelica(version="3.2.3")));
end Heater;
