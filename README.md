

<h1>FAN-CONTROLLER</h1>
<h2>RPM Calculation and PWM-Based Fan Control</h2>

<h3>Overview</h3>
<p>This project implements an RPM (Revolutions Per Minute) calculation system and a PWM (Pulse Width Modulation) based fan control mechanism for an embedded system. A median filter is implemented to obtain stable RPM output.</p>

<h3>Tech Stack</h3>

<h4>Languages:</h4>
<ul>
  <li>Embedded C</li>
</ul>

<h4>Tools and Platforms:</h4>
<ul>
  <li><strong>Integrated Development Environment (IDE):</strong> Visual Studio Code
    <ul>
      <li>Used for writing, compiling, and debugging the code.</li>
    </ul>
  </li>
  <li><strong>Platform IO:</strong>
    <ul>
      <li>An open-source ecosystem for Embedded Systems development, integrated into Visual Studio Code.</li>
    </ul>
  </li>
  <li><strong>Version Control System:</strong> Git
    <ul>
      <li>For version control and collaboration.</li>
    </ul>
  </li>
</ul>

<h4>Libraries and Frameworks:</h4>
<ul>
  <li><strong>AVR Library:</strong>
    <ul>
      <li>Standard C library for AVR microcontrollers, providing functions for I/O and peripheral control.</li>
    </ul>
  </li>
</ul>

<h4>Hardware:</h4>
<ul>
  <li><strong>Microcontroller:</strong>
    <ul>
      <li>AVR-based microcontroller (ATmega16U4/ATmega32U4).</li>
    </ul>
  </li>
  <li><strong>PWM-controllable Fan:</strong>
    <ul>
      <li>Fan with PWM input for speed control.</li>
    </ul>
  </li>
</ul>
