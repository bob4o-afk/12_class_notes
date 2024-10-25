plugins {
    id("java")
    id("application")
}

group = "org.example"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    testImplementation(platform("org.junit:junit-bom:5.10.0"))
    testImplementation("org.junit.jupiter:junit-jupiter")
}

tasks.test {
    useJUnitPlatform()
}

application {
    mainClass.set("org.example.AsyncFileTransferServer")
}

tasks.register<JavaExec>("runClient") {
    mainClass.set("org.example.AsyncFileTransferClient")
    classpath = sourceSets["main"].runtimeClasspath
}
